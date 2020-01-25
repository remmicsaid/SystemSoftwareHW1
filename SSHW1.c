#define MAX_DATA_STACK_HEIGHT 23
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVELS 3
#include <stdio.h>
#include <stdlib.h>

// Questions:
// Are instructions going to be passed to main as integer arrays or integers?
// Is the code going to be tested with a different main method?
// How are we going to implement data area and text area?

typedef struct oplm {
    int op;   // opcode
    int  l;   // L
    int  m;   // M
}instruction;

instruction *create_instruction(int op, int l, int m)
{
  instruction *i = calloc(1, sizeof(instruction));
  i->op = op;
  i->l = l;
  i->m = m;

  return i;
}

int fetchCycle()
{

}

int executionCycle()
{

}

int main(int argc, char **argv)
{
  // Reading the instrustions
  char *filename = argv[1];
  FILE *fp;
  if (fp = fopen(filename, "r"))
  {
    fp = fopen(filename, "r");
    printf("File opened\n");
  }
  else
  {
    printf("err: file not found");
    return 0;
  }

  char buffer[500] = {0}, c;
  int op, l, m, SP, BP, PC, IR, GP, HALT, i = 0;

  printf("while loop initiated\n");
  while (!feof(fp))
  {
    // buffer[i++] = fgetc(fp);
    // printf("%s", buffer);
    printf("%c", fgetc(fp));
  }
  printf("while loop completed\n");

  // Processing instructions
  // Loop throught the file, assign corresponding values to op, l, and m,
  // execute instructions that op, l, and m signify, and repeat until complete.
  //   ^
  //   I think this loop should probably be in the fetchCycle() function along with
  //   some of the surrounding code
  instruction *ir = create_instruction(op, l, m);

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

  // while(HALT == 0)
  // {
  //    // fetch{
  //    //
  //    //
  //    // }
  //
  //    switch(ir->op){
  //
  //  case 1:
  //      //LIT    0, M
  //      //if (bp = = 0) {
  //      //gp = gp + 1 ;
  //      //stack[gp]  M ;
  //      //}
  //      //else {
  //      //sp  sp - 1;
  //      //stack[sp]  M;
  //      //}
  //   break;
  //
  //  case 2:
  //      //OPR 0, #   ( 0  ≤  #  ≤  13 )
  //      //see document
  //   break;
  //
  //  case 3:
  //      //LOD   L, Mif (base(L, bp) = = 0)
  //      //{gp = gp + 1; stack[gp]  stack[ base(L, bp) + M];
  //      //}
  //      //else   { sp   sp - 1; stack[sp]  stack[ base(L, bp) - M];}
  //   break;
  //
  //  case 4:
  //      //STO L, Mif (base(L, bp) = = 0)
  //      //{stack[ base(L, bp) + M] stack[gp]; gp = gp – 1;}else   {stack[ base(L, bp) - M] stack[sp]; sp  sp + 1;}
  //   break;
  //
  //  case 5:
  //      //CAL   L, Mif (sp – 4 ≤ gp) Error_StakOverflow ( );stack[sp - 1]   0/* space to return valuestack[sp - 2]    base(L, bp); /* static link (SL)stack[sp - 3]   bp;/* dynamic link (DL)stack[sp - 4]   pc/* return address (RA) bp  sp - 1;pc M;
  //      break;
  //
  //  case 6:
  //      //INC    0, Mif (sp – M ≤ gp) Error_StakOverflow ( );if (bp = = 0) gp = gp + Melse sp  sp - M;
  //      break;
  //
  //  case 7:
  //      //JMP   0, Mpc M;
  //      break;
  //
  //  case 8:
  //      //JPC    0, M if stack[sp] == 0 then { pc M; }sp  sp + 1;
  //      break;
  //
  //  case 9:
  //      //SIO 0, 1print(stack[sp]);sp  sp + 1;
  //      break;
  //
  //  case 10:
  //      //SIO   0, 2sp  sp - 1;read(stack[sp]);
  //      break;
  //
  //   default:
  //       //SIO   0, 3Set Halt flag to one;
  //       HALT = 1;
  //
  //      }
  //   }
    fclose(fp);
    return 0;
}
