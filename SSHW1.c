#define MAX_DATA_STACK_HEIGHT 23
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVELS 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct oplm {
    int op;   // opcode
    int reg;
    int  l;   // L
    int  m;   // M
}instruction;

int fetchCycle(char *list);
int executionCycle(instruction *ir);

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
  int op, reg, l, m, len = strlen(list);
  int pc = 0;
  // Assigns op, l, and m to the correct values and returns if the input was not
  // given in sets of three integers.
    
    /*
     ok i think something like this would work 
     
     fscanf(file, "%d %d %d %d", &op, &reg, &l, &m);
     
     this should collect the first line and then maybe we can make a function to call the lines one by one until we hit sio
    
    */
  if ( (len % 4) == 0)
  {
    
      op = list[pc] - '0';
      pc++;
      reg = list[pc] - '0';
      pc++;
      l = list[pc] - '0';
      pc++;
      m = list[pc] - '0';
      pc++;
        
    }
    
    else
    {
     return 0;   
    }
    
    instruction *inst = create_instruction(op, reg, l, m);
    // tells main if a call to execution cycle failed
    if (!executionCycle(inst))
    {
      printf("err: executionCycle failed\n");
      return 0;
    }
    
    return 1;
  }
  


int executionCycle(instruction *ir)
{
  int SP, BP, PC, IR, GP, HALT;
  int data_stack[41];
    
  for(int a = 0; a<40; a++)
  {
     data_stack[a] = 0;   
  }
  
    
  SP = MAX_DATA_STACK_HEIGHT;
  BP = 0;
  PC = 0;
  IR  = 0;
  GP = -1;
  HALT = 1;
  int i =0;

  while(HALT == 1)
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
       reg[i] = m;
    break;

   case 2:
       //OPR 0, #   ( 0  ≤  #  ≤  13 )
       //see document
            
       sp = bp - 1;
       bp = stack[sp + 3];
       pc = stack[sp + 4];
    break;

   case 3:
       //LOD   L, Mif (base(L, bp) = = 0)
       //{gp = gp + 1; stack[gp]  stack[ base(L, bp) + M];
       //}
       //else   { sp   sp - 1; stack[sp]  stack[ base(L, bp) - M];}
       reg[i] = stack[ base(L, bp) + M];
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
        HALT = 0;

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
