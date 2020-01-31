// Michael Said
// Liam May
// COP 3402
// Spring 2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_DATA_STACK_HEIGHT 23
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVELS 3

int *fetchCycle(int *code, int *ir, int pc);
void executionCycle(int *code);
int base(int l, int base, int* data_stack);

// Returns the integer array that make a specific instruction to executionCycle
// to be processed. Takes in as arguments the array of all instructions, the array
// to be returned, and a counter which signals the instruction being requested.
int *fetchCycle(int *code, int *ir, int pc)
{
  int index = pc * 4;
  if (index % 4 == 0)
  {
    ir[pc] = code[index];
    // continue;
  }
  if (pc % 4 == 1)
  {
    ir[pc] = code[index];
    // continue;
  }
  if (pc % 4 == 2)
  {
    ir[pc] = code[index];
    // continue;
  }
  if (pc % 4 == 3)
  {
    ir[pc] = code[index];
    // continue;
  }

  return ir;
}


// takes in a single instruction and executes the command of that instruction
void executionCycle(int *code)
{
  int l, m, sp = MAX_DATA_STACK_HEIGHT, bp = 0, pc = 0, gp = -1, halt = 0, i = 0, *ir;
  int data_stack[41] = {0}, reg[200];

  ir = fetchCycle(code, ir, pc++);
  while (halt == 0)
  {
    switch(ir[0])
    {
       case 1:
        reg[i] = m;
        break;

       case 2:
        sp = bp - 1;
        bp = data_stack[sp + 3];
        pc = data_stack[sp + 4];
        break;

       case 3:
        reg[i] = data_stack[base(l, bp, data_stack) + m];
        break;

       case 4:
        data_stack[ base(l, bp, data_stack) + m] = reg[i];
        break;

       case 5:
        data_stack[sp + 1]  = 0;
        data_stack[sp + 2]  =  base(l, bp, data_stack);
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

      case 11:
        break;

      case 12:
        break;

      case 13:
        break;

      case 14:
        break;

      case 15:
        break;

      case 16:
        break;

      case 17:
        break;

      case 18:
        break;

      case 19:
        break;

      case 20:
        break;

      case 21:
        break;

      default:
        halt = 1;
        printf("err: instrunction %d not valid\n", pc);
      }
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

int main(int argc, char **argv)
{
  // Reading the instrustions
  int i = 0, j = 1, len, num, code[MAX_CODE_LENGTH];
  char *filename = argv[1], buffer[MAX_CODE_LENGTH] = {'\0'}, c;
  FILE *fp;

  // opening the file
  if (fp != NULL)
  {
    fp = fopen(filename, "r");
  }
  else
  {
    printf("err: file not found\n");
    return 0;
  }

  printf("Contents being scanned into array:\n");
  // Copying the file contents into an integer array
  // fscanf called here to get initial value that is evaluated in order to start
  // the loop
  fscanf(fp, "%d", &num);
  while (!feof(fp))
  {
    // Prints values as they are scanned in rows of 4
    (j++ % 4 == 0) ? printf("%d\n", num) : printf("%d ", num);

    code[i++] = num;
    fscanf(fp, "%d", &num);
  }
  // Prints last value scanned
  printf("%d\n", num);

  // printf("\n\nContents of code array after transfer:\n");
  // for (i = 0; i < j; i++)
  // {
  //   printf("%d\n", code[i]); // I guess the last value in the array is garbage?
  // }

  executionCycle(code);

  fclose(fp);
  return 0;
}
