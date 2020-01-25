#define MAX_DATA_STACK_HEIGHT 23
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVELS 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct oplm {
    int op;   // opcode
    int  l;   // L
    int  m;   // M
}instruction;

int fetchCycle(char *list);
int executionCycle(instruction *ir);

instruction *create_instruction(int op, int l, int m)
{
  instruction *i = calloc(1, sizeof(instruction));
  i->op = op;
  i->l = l;
  i->m = m;

  return i;
}

// Parses through the array sent and makes sure the instructions are valid
int fetchCycle(char *list)
{
  int op, l, m, i, len = strlen(list);
  // Assigns op, l, and m to the correct values and returns if the input was not
  // given in sets of three integers.
  while (1)
  {
    if (i < len)
    {
      op = list[i] - '0';
    }
    else
    {
      printf("err: input must be in sets of threes\n");
      return 0;
    }
    if (i < len)
    {
      l = list[i] - '0';
    }
    else
    {
      printf("err: input must be in sets of threes\n");
      return 0;
    }
    if (i < len)
    {
      m = list[i] - '0';
    }
    else
    {
      printf("err: input must be in sets of threes\n");
      return 0;
    }

    instruction *ir = create_instruction(op, l, m);
    // tells main if a call to execution cycle failed
    if (!executionCycle(ir))
    {
      printf("err: executionCycle failed\n");
      return 0;
    }
  }
  return 1;
}

int executionCycle(instruction *ir)
{
  int op, l, m, SP, BP, PC, IR, GP, HALT;
  /*
  Initial “data-stack” store values:
  data-stack[0] =0;
  data-stack[1] =0;
  ...;
  data-stack[n-1] =0;
  */

  //scanf("%d %d %d", &op, &l, &m);

  SP = MAX_DATA_STACK_HEIGHT;
  BP = 0;
  PC = 0;
  IR  = 0;
  GP = -1;
  HALT = 0;

  /*
  BrainStorming

  In class he also set the switch statement to ir.op

  maybe a recursive function would help
  */

  while(HALT == 0)
  {
     // fetch{
     //
     //
     // }

     switch(ir->op){

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
    break;

   case 2:
       //OPR 0, #   ( 0  ≤  #  ≤  13 )
       //see document
    break;

   case 3:
       //LOD   L, Mif (base(L, bp) = = 0)
       //{gp = gp + 1; stack[gp]  stack[ base(L, bp) + M];
       //}
       //else   { sp   sp - 1; stack[sp]  stack[ base(L, bp) - M];}
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
        //SIO   0, 3Set Halt flag to one;
        HALT = 1;

       }
    }
}

int main(int argc, char **argv)
{
  // Reading the instrustions
  int i = 0;
  char *filename = argv[1], buffer[500] = {0}, c;
  FILE *fp;
  if (fp = fopen(filename, "r"))
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
    if (isdigit(c))
    {
      buffer[i] = c;
    }
    i++;
  }
  // printf("while loop completed\n");

  fclose(fp);
  return 0;
}
