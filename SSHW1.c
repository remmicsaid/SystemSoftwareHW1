#define MAX_DATA_STACK_HEIGHT 23
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVELS 3
#include <stdio.h>
#include <stdlib.h>

// Questions:
// Are instructions going to be passed to main as integer arrays or integers?
// I think integer arrays because the input file has 7 0 10 as the first line and the op code relies on 7 for the instruction

// Is the code going to be tested with a different main method?
// 

// How are we going to implement data area and text area?
// the data area being the stack (?) and is the text area supposed to be the file we're inputting?
// In class he said the stack is growing downwards which should have something to do with the sp (&gp?)
// People were also saying there was a lot of copy and pasting so I think if we implement it by using the code
// from appendix B that should work ??

// Do you make the input file? Can you send that to me?

typedef struct oplm {
    int op;   // opcode
    int  l;   // L
    int  m;   // M
}instruction;

struct instruction *create_instruction(int op, int l, int m)
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
  //argc = number of arguments
  //**argv = double array representing the instr
  // Reading the instrustions
  char *filename = argv[1];
  FILE *fp;
  if (fp = fopen(filename, "r"))
  {
    fp = fopen(filename, "r");
    //printf("File opened\n");
  }
  else
  {
    //printf("err: file not found");
    return 0;
  }

  char buffer[500] = {0}, c;
  int SP, BP, PC, IR, GP, HALT, i = 0;
    //^deleted op, l, m from here which will mess up part of the code
    // he gives us line 22, should include them in a node?

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

  

  int SP = MAX_DATA_STACK_HEIGHT;
  int BP = 0;
  int PC = 0;
  int IR  = 0;
  int GP = -1;
  int HALT = 0;

  
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
}// Michael Said
// Liam May
// COP 3402
// Spring 2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_DATA_STACK_HEIGHT 40
#define MAX_CODE_LENGTH 200
#define MAX_LEXI_LEVELS 3

typedef struct{
  int op;
  int r;
  int l;
  int m;
}instruction;

instruction *create_instruction(int op, int r, int l, int m);
instruction *fetchCycle(int *code, instruction *ir, int pc);
void executionCycle(int *code);
int base(int l, int base, int* data_stack);

// Given the four values that make up an instruction, returns the address of
// an instruction type object
instruction *create_instruction(int op, int r, int l, int m)
{
	instruction *i = calloc(1, sizeof(instruction));
	i->op = op;
  i->r = r;
  i->l = l;
  i->m = m;

	return i;
}

// Returns the integer array that make a specific instruction to executionCycle
// to be processed. Takes in as arguments the array of all instructions, the array
// to be returned, and a counter which signals the instruction being requested.
instruction *fetchCycle(int *code, instruction *ir, int pc)
{
  int index = pc * 4;
  // printf("accessing code[%d]\n", index);
  ir->op = code[index++];
  // index++;
  // printf("accessing code[%d]\n", index);
  ir->r = code[index++];
  // index++;
  // printf("accessing code[%d]\n", index);
  ir->l = code[index++];
  // index++;
  // printf("accessing code[%d]\n", index);
  ir->m = code[index];
  return ir;
}

void super_output(int pc, int bp, int sp,int data_stack[], int reg[], int activate)
{
  int x;
  int g =0;
  printf("%d\t%d\t%d\t", pc, bp, sp);
  for (x = 0; x < 8; x++)
  {
    printf("%d ", reg[x]);
  }
  printf("\nStack:");
  for (x = 1; x < sp; x++)
  {
    if(activate == 1 && g ==6)
    {
      printf("|");
    }
    g++;

    //if( x != 7)
    //{
        printf("%d ", data_stack[x]);
    //}
    if(x == 7)
    {
      sp = sp+1;
    }

  }
  printf("\n");
  return;
}

// takes in a single instruction and executes the command of that instruction
void executionCycle(int *code)
{
  int sp = 0, bp = 1, pc = 0, halt = 1, i = 0, activate = 0, x;
  int data_stack[MAX_DATA_STACK_HEIGHT] = {0}, reg[8] = {0};
  instruction *ir = create_instruction(0, 0, 0, 0);

  // Capturing instruction integers indicated by program counter
  ir = fetchCycle(code, ir, pc);



  printf("\t\tpc\tbp\tsp\tregisters\n");
  printf("Initial values\t%d\t%d\t%d\t", pc, bp, sp);
  for (x = 0; x < 8; x++)
  {
    printf("%d ", reg[x]);
  }
  printf("\nStack: ");
  for (x = 0; x < MAX_DATA_STACK_HEIGHT; x++)
  {
    printf("%d ", data_stack[x]);
  }
  printf("\n");

  while (halt == 1)
  {
    // printf("6\n");
    switch(ir->op)
    {
       case 1:
        printf("%d lit %d %d %d\t", ((pc - 1) < 0) ? 0 : pc - 1, ir->r, ir->l, ir->m);
        reg[ir->r] = ir->m;
        super_output(pc, bp, sp, data_stack, reg, activate);
        break;

       case 2:
        printf("%d rtn %d %d %d\t", ((pc - 1) < 0) ? 0 : pc - 1, ir->r, ir->l, ir->m);
        sp = bp - 1;
        bp = data_stack[sp + 3];
        pc = data_stack[sp + 4];
        super_output(pc, bp, sp, data_stack, reg, activate);
        break;

       case 3:
        printf("%d lod %d %d %d\t", ((pc - 1) < 0) ? 0 : pc - 1, ir->r, ir->l, ir->m);
        reg[ir->r] = data_stack[base(ir->l, bp, data_stack) + ir->m];
        super_output(pc, bp, sp, data_stack, reg, activate);
        break;

       case 4:
        printf("%d sto %d %d %d\t", ((pc - 1) < 0) ? 0 : pc - 1, ir->r, ir->l, ir->m);
        data_stack[ base(ir->l, bp, data_stack) + ir->m] = reg[ir->r];
        super_output(pc, bp, sp, data_stack, reg, activate);
        break;

       case 5:
        printf("%d cal %d %d %d\t", ((pc - 1) < 0) ? 0 : pc - 1, ir->r, ir->l, ir->m);
        data_stack[sp + 1]  = 0;
        data_stack[sp + 2]  =  base(ir->l, bp, data_stack);
        data_stack[sp + 3]  = bp;
        data_stack[sp + 4]  = pc;
        bp = sp + 1;
        pc = ir->m;
        super_output(pc, bp, sp, data_stack, reg, activate);
        activate = 1;
        break;

       case 6:
         printf("%d inc %d %d %d\t", ((pc - 1) < 0) ? 0 : pc - 1, ir->r, ir->l, ir->m);
         sp = sp + ir->m;
         super_output(pc, bp, sp, data_stack, reg, activate);
         break;

       case 7:
         printf("%d jmp %d %d %d\t", ((pc - 1) < 0) ? 0 : pc - 1, ir->r, ir->l, ir->m);
         pc = ir->m;
         super_output(pc, bp, sp, data_stack, reg, activate);
         break;

       case 8:
         printf("%d jpc %d %d %d\t", ((pc - 1) < 0) ? 0 : pc - 1, ir->r, ir->l, ir->m);
         if(reg[ir->r] == 0)
         {
             pc = ir->m;
         }
         super_output(pc, bp, sp, data_stack, reg, activate);
         break;

////////////////////////////////////?????????????????????
       case 9:
         printf("%d sio %d %d %d\t", ((pc - 1) < 0) ? 0 : pc - 1, ir->r, ir->l, ir->m);
         printf("%d", reg[ir->r]);
         super_output(pc, bp, sp, data_stack, reg, activate);
         break;

         case 10:
           printf("%d sio %d %d %d\t", ((pc - 1) < 0) ? 0 : pc - 1, ir->r, ir->l, ir->m);
           //stated in class to let the user know what they were scanning in
           printf("read in the register at index ir->r");
           scanf("%d", &reg[ir->r]);
           super_output(pc, bp, sp, data_stack, reg, activate);
           break;

        case 11:
          printf("%d sio %d %d %d\t", ((pc - 1) < 0) ? 0 : pc - 1, ir->r, ir->l, ir->m);
          halt = 0;
          super_output(pc, bp, sp, data_stack, reg, activate);
          break;

        case 12:
          printf("%d neg %d %d %d\t", ((pc - 1) < 0) ? 0 : pc - 1, ir->r, ir->l, ir->m);
          reg[ir->r] = -reg[ir->r];
          super_output(pc, bp, sp, data_stack, reg, activate);
          break;

        case 13:
          printf("%d add %d %d %d\t", ((pc - 1) < 0) ? 0 : pc - 1, ir->r, ir->l, ir->m);
          reg[ir->r] = reg[ir->l] + reg[ir->m];
          super_output(pc, bp, sp, data_stack, reg, activate);
          break;

        case 14:
          printf("%d sub %d %d %d\t", ((pc - 1) < 0) ? 0 : pc - 1, ir->r, ir->l, ir->m);
          reg[ir->r] = reg[ir->l] - reg[ir->m];
          super_output(pc, bp, sp, data_stack, reg, activate);
          break;

        case 15:
          printf("%d mul %d %d %d\t", ((pc - 1) < 0) ? 0 : pc - 1, ir->r, ir->l, ir->m);
          reg[ir->r] = reg[ir->l] * reg[ir->m];
          super_output(pc, bp, sp, data_stack, reg, activate);
          break;

        case 16:
          printf("%d div %d %d %d\t", ((pc - 1) < 0) ? 0 : pc - 1, ir->r, ir->l, ir->m);
          reg[ir->r] = reg[ir->l] / reg[ir->m];
          super_output(pc, bp, sp, data_stack, reg, activate);
          break;

        case 17:
          printf("%d odd %d %d %d\t", ((pc - 1) < 0) ? 0 : pc - 1, ir->r, ir->l, ir->m);
          reg[ir->r] = reg[ir->l] % 2;
          super_output(pc, bp, sp, data_stack, reg, activate);
          break;

        case 18:
          printf("%d mod %d %d %d\t", ((pc - 1) < 0) ? 0 : pc - 1, ir->r, ir->l, ir->m);
          reg[ir->r] = reg[ir->l] %  reg[ir->m];
          super_output(pc, bp, sp, data_stack, reg, activate);
          break;

        case 19:
          printf("%d eql %d %d %d\t", ((pc - 1) < 0) ? 0 : pc - 1, ir->r, ir->l, ir->m);
          reg[ir->r] = reg[ir->l] == reg[ir->m];
          super_output(pc, bp, sp, data_stack, reg, activate);
          break;

        case 20:
          printf("%d neq %d %d %d\t", ((pc - 1) < 0) ? 0 : pc - 1, ir->r, ir->l, ir->m);
          reg[ir->r] = reg[ir->l] != reg[ir->m];
          super_output(pc, bp, sp, data_stack, reg, activate);
          break;

        case 21:
          printf("%d lss %d %d %d\t", ((pc - 1) < 0) ? 0 : pc - 1, ir->r, ir->l, ir->m);
          reg[ir->r] = reg[ir->l] < reg[ir->m];
          super_output(pc, bp, sp, data_stack, reg, activate);
          break;

        case 22:
          printf("%d leq %d %d %d\t", ((pc - 1) < 0) ? 0 : pc - 1, ir->r, ir->l, ir->m);
          reg[ir->r] = reg[ir->l] <= reg[ir->m];
          super_output(pc, bp, sp, data_stack, reg, activate);
          break;

         case 23:
          printf("%d gtr %d %d %d\t", ((pc - 1) < 0) ? 0 : pc - 1, ir->r, ir->l, ir->m);
          reg[ir->r] = reg[ir->l] <= reg[ir->m];
          super_output(pc, bp, sp, data_stack, reg, activate);
          break;

        default:
          printf("%d geq %d %d %d\t", ((pc - 1) < 0) ? 0 : pc - 1, ir->r, ir->l, ir->m);
          reg[ir->r] = reg[ir->l] >= reg[ir->m];
          super_output(pc, bp, sp, data_stack, reg, activate);
      }
      // printf("Instruction executed...\n");

      ir = fetchCycle(code, ir, pc++);

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

void output(int* code, int i)
{
    int* op, r, l, m;
    printf("Line \t OP \t R \t L \t M\n");
    int lines = i/4;
    int k =0;
    for(int j=0; j<=lines; j++)
    {
        printf("%d \t", j); // line
        switch (code[k])
        {
          case 1:
            printf("lit \t");
            break;

          case 2:
            printf("rtn \t");
            break;

          case 3:
            printf("lod \t");
            break;

          case 4:
            printf("sto \t");
            break;

          case 5:
            printf("cal \t");
            break;

          case 6:
            printf("inc \t");
            break;

          case 7:
            printf("jmp \t");
            break;

          case 8:
            printf("jpc \t");
            break;

          case 9:
            printf("sio \t");
            break;

          case 10:
            printf("sio \t");
            break;

          case 11:
            printf("sio \t");
            break;

          case 12:
            printf("neg \t");
            break;

          case 13:
            printf("add \t");
            break;

          case 14:
            printf("sub \t");
            break;

          case 15:
            printf("mul \t");
            break;

          case 16:
            printf("div \t");
            break;

          case 17:
            printf("odd \t");
            break;

          case 18:
            printf("mod \t");
            break;

          case 19:
            printf("eql \t");
            break;

          case 20:
            printf("neq \t");
            break;

          case 21:
            printf("lss \t");
            break;

          case 22:
            printf("leq \t");
            break;

          case 23:
            printf("gtr \t");
            break;

          case 24:
            printf("geq \t");
            break;
        }
        k++;
        printf("%d \t", code[k]); // r
        k++;
        printf("%d \t", code[k]); // l
        k++;
        printf("%d \n", code[k]); // m
        k++;
    }
}


int main(int argc, char **argv)
{
  // Reading the instrustions
  int i = 0, j = 1, len, num, code[MAX_CODE_LENGTH];
  char *filename = argv[1], buffer[MAX_CODE_LENGTH] = {'\0'}, c;
  FILE *fp;

  // opening the file
  fp = fopen(filename, "r");

  // printf("Contents being scanned into array:\n");

  // Copying the file contents into an integer array
  // fscanf called here to get initial value that is evaluated in order to start
  // the loop
  fscanf(fp, "%d", &num);
  while (!feof(fp))
  {
    // Prints values as they are scanned in rows of 4
    // (j++ % 4 == 0) ? printf("%d\n", num) : printf("%d ", num);
    code[i] = num;
    i++;
    fscanf(fp, "%d", &num);
  }
  code[i] = num;
  // printf("%d\n", num);

  output(code, i);
  executionCycle(code);

  fclose(fp);
  return 0;
}

