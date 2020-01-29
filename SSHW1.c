// Michael Said
// Liam May
// COP 3402
// Spring 2020

#define MAX_DATA_STACK_HEIGHT 23
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVELS 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct oplm {
    int op; // opcode
    int reg; // register
    int l; // L
    int m; // M
}instruction;

instruction *create_instruction(int op, int reg, int l, int m);
int fetchCycle(char *list);
int executionCycle(instruction *ir);
instruction *toInstruction(char *str);
void printInstructions(instruction *arr, int len);
void burnIt(instruction *arr, int len);

instruction *create_instruction(int op, int reg, int l, int m)
{
  instruction *i = calloc(1, sizeof(instruction));
  i->op = op;
  i->reg = reg;
  i->l = l;
  i->m = m;

  return i;
}

// Parses through the array sent and makes sure the instructions are valid
int fetchCycle(char *list)
{
  int op, l, m, pc, reg, len = strlen(list);
  pc = 0;
  // Assigns op, l, and m to the correct values and returns if the input was not
  // given in sets of three integers.
  // if ( (len % 4) == 0)
  // {
  //   op = list[pc] - '0';
  //   pc++;
  //   reg = list[pc] - '0';
  //   pc++;
  //   l = list[pc] - '0';
  //   pc++;
  //   m = list[pc] - '0';
  //   pc++;
  // }
  // else
  // {
  //   return 0;
  // }
  //
  // instruction *inst = create_instruction(op, reg, l, m);
  // tells main if a call to execution cycle failed
  // if (!executionCycle(inst))
  // {
  //   printf("err: executionCycle failed\n");
  //   return 0;
  // }

  return 1;
}

int executionCycle(instruction *inst)
{
  int sp, bp, pc, ir, gp, halt, m;
  int data_stack[41], reg[200];

  for(int a = 0; a<40; a++)
  {
     data_stack[a] = 0;
  }


  sp = MAX_DATA_STACK_HEIGHT;
  bp = 0;
  pc = 0;
  ir  = 0;
  gp = -1;
  halt = 1;
  int i = 0;

  while(halt == 1)
  {
     // fetch{
     //
     //
     // }

   switch(inst->op){

   case 1:
       //LIT    0, M
       //if (bp = = 0) {
       //gp = gp + 1 ;
       //stack[gp]  M ;
       //}
       //else {
       //sp  sp - 1;
       //stack[sp]  M;
       //}
       reg[i] = m;
    break;

   case 2:
       //OPR 0, #   ( 0  ≤  #  ≤  13 )
       //see document

       sp = bp - 1;
       bp = data_stack[sp + 3];
       pc = data_stack[sp + 4];
    break;

   case 3:
       //LOD   L, Mif (base(L, bp) = = 0)
       //{gp = gp + 1; stack[gp]  stack[ base(L, bp) + M];
       //}
       //else   { sp   sp - 1; stack[sp]  stack[ base(L, bp) - M];}
       // reg[i] = data_stack[ base(L, bp) + M];
    break;

   case 4:
       //STO L, Mif (base(L, bp) = = 0)
       //{stack[ base(L, bp) + M] stack[gp]; gp = gp – 1;}else   {stack[ base(L, bp) - M] stack[sp]; sp  sp + 1;}
    break;

   case 5:
       //CAL   L, Mif (sp – 4 ≤ gp) Error_StakOverflow ( );stack[sp - 1]   0/* space to return valuestack[sp - 2]    base(L, bp); /* static link (SL)stack[sp - 3]   bp;/* dynamic link (DL)stack[sp - 4]   pc/* return address (RA) bp  sp - 1;pc M;
       break;

   case 6:
       //INC    0, Mif (sp – M ≤ gp) Error_StakOverflow ( );if (bp = = 0) gp = gp + Melse sp  sp - M;
       break;

   case 7:
       //JMP   0, Mpc M;
       break;

   case 8:
       //JPC    0, M if stack[sp] == 0 then { pc M; }sp  sp + 1;
       break;

   case 9:
       //SIO 0, 1print(stack[sp]);sp  sp + 1;
       break;

   case 10:
       //SIO   0, 2sp  sp - 1;read(stack[sp]);
       break;

    default:
        //SIO   0, 3Set halt flag to one;
        halt = 0;

       }
    }
}

// Takes in string of integers representing instructions and the address of
// an array of instructions. Then parses the integer values out of the string
// and assigns them to the corresponding values within an instruction struct.
// This function returns an ordered array of all of the instructions.
instruction *toInstruction(char *str)
{
  int count = 1, op, reg, l, m, len = strlen(str), i = 0;
  instruction *thisInst;

  instruction *theseInstructions = malloc((sizeof(instruction) * len) + 1);
  char *token = " ";
  while (token != NULL)
  {
    token = strtok(str, " ");
    if (count % 4 == 1)
    {
      // putting every first value in op field
      op = atoi(token);
    }
    if (count % 4 == 2)
    {
      // putting every second value in the reg field
      reg = atoi(token);
    }
    if (count % 4 == 3)
    {
      // putting every third value in the l field
      l = atoi(token);
    }
    if (count % 4 == 0)
    {
      // putting every fourth value in the m field
      m = atoi(token);
    }
    // creating an instruction object with the four fields
    *thisInst = *create_instruction(op, reg, l, m);
    // adding this instruction object to the array of instructions before the
    // fields get overwritten with the next set of instructions
    theseInstructions[i++] = *thisInst;
  }
  return theseInstructions;
}

void printInstructions(instruction *arr, int len)
{
  int i;
  for (i = 0; i < len; i++)
  {
    printf("instruction %d: %d %d %d %d\n", i, arr[i]->op, arr[i]->reg, arr[i]->l, arr[i]->m);
  }
}

// frees all of the dynamically allocated memory from the instruction array
void burnIt(instruction *arr, int len)
{
  int i;
  for (i = 0; i < len; i++)
  {
    free(arr[i]);
  }
  free(arr);
}

int main(int argc, char **argv)
{
  // Reading the instrustions
  int i = 0, j = 0, len;
  char *filename = argv[1], buffer[MAX_CODE_LENGTH] = {'\0'}, c;
  FILE *fp;
  instruction *theseInstructions;

  if (fp != NULL)
  {
    fp = fopen(filename, "r");
    // printf("File opened\n");
  }
  else
  {
    printf("err: file not found");
    return 0;
  }

  // Collecting file input
  while (!feof(fp))
  {
    c = fgetc(fp);
    buffer[i++] = c;
  }
  len = strlen(buffer);

  theseInstructions = toInstruction(buffer);
  printInstructions(theseInstructions, len);
  burnIt(theseInstructions, len);

  fclose(fp);
  return 0;
}

