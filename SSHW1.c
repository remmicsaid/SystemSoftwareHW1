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
void fetchCycle(instruction *theseInstructions, int len);
void executionCycle(instruction *ir);
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

// iterates through array of instructions and sends them to executionCycle
void fetchCycle(instruction *theseInstructions, int len)
{
  int i;

  for (i = 0; i < len; i++)
  {
    executionCycle(&theseInstructions[i]);
  }

  return;
}

int base(int l, int base, int* data_stack)
// l stand for L in the instruction format
{
    int b1; //find base L levels down
    b1 = base;
    while (l > 0)
    {
        b1 = data_stack[b1 + 1];
        l--;

    }
    return b1;
}

// takes in a single instruction and executes the command of that instruction
void executionCycle(instruction *inst)
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

   switch(inst->op){

   case 1:

    reg[i] = m;
    break;

   case 2:

    sp = bp - 1;
    bp = data_stack[sp + 3];
    pc = data_stack[sp + 4];
    break;

   case 3:

    reg[i] = data_stack[base(inst->l, bp, data_stack) + m];
    break;

   case 4:

    data_stack[ base(inst->l, bp, data_stack) + m] = reg[i];
    break;

   case 5:

    data_stack[sp + 1]  = 0;
    data_stack[sp + 2]  =  base(inst->l, bp, data_stack);
    //base is a function
    data_stack[sp + 3]  = bp;
    data_stack[sp + 4]  = pc;
    bp = sp + 1;
    pc = m;
    break;

   case 6:

       sp = sp + m;
       break;

   case 7:

       pc = m;
       break;

   case 8:

       if(reg[i] == 0)
       {
           pc = m;
       }
       break;

   case 9:

       printf("%d", reg[i]);
       break;

   case 10:

       //new version says read reg[i];
       //In class, he says to scan and output something, not sure what to output
       scanf("%d", &reg[i]);
       break;

    default:

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
    printf("instruction %d: %d %d %d %d\n", i, arr[i].op, arr[i].reg, arr[i].l, arr[i].m);
  }
}



// frees all of the dynamically allocated memory from the instruction array
void burnIt(instruction *arr, int len)
{
  int i;
  for (i = 0; i < len; i++)
  {
    free(&arr[i]);
  }
  free(arr);
}

int main(int argc, char **argv)
{
  // Reading the instrustions
  int i = 0, j = 0, len, retval;
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

  // converting char input to ints then to instructions and storing those
  // instructions in an array
  printf("toInstruction...\n");
  theseInstructions = toInstruction(buffer);
  // testing toInstruction by printing array of instructions
  printf("printInstructions...\n");
  printInstructions(theseInstructions, len);
  // sending array of instructions to be processed
  printf("fetchCycle...\n");
  fetchCycle(theseInstructions, len);
  printf("burnIt...\n");
  burnIt(theseInstructions, len);

  fclose(fp);
  return 0;
}
