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

void fetchCycle(int *arr, int size);
void executionCycle(int op, int reg, int l, int m);

// Takes in an array of integers representing instructions and sends them to
// executionCycle to be processed
void fetchCycle(int *arr, int len)
{
  // capturing the length of the int array
  int i, op = 0, r = 0, l = 0, m = 0;

  printf("\n\nSize of array: %d\nValues successfully passed:\n======================\n", len);

  // loops through all integers in arr and sends the values in sets of four to
  // executionCycle
  for (i = 0; i < len; i++)
  {
    if (i % 4 == 0)
    {
      op = arr[i];
      // continue;
    }
    if (i % 4 == 1)
    {
      r = arr[i];
      // continue;
    }
    if (i % 4 == 2)
    {
      l = arr[i];
      // continue;
    }
    if (i % 4 == 3)
    {
      m = arr[i];
      // continue;
    }
    printf("calling executionCycle...\n"); // why are these lines not executing?
    executionCycle(op, r, l, m);
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
void executionCycle(int op, int r, int l, int m)
{
  int sp, bp, pc, ir, gp, halt;
  int data_stack[41] = {0}, reg[200];

  sp = MAX_DATA_STACK_HEIGHT;
  bp = 0;
  pc = 0;
  ir  = 0;
  gp = -1;
  halt = 0;
  int i = 0;

  // printf("< %d , %d , %d , %d >\n", op, r, l, m);

  while (halt == 0) // This is an infinite loop right now because we need to be
                    // calling fetchCycle from within this function, not the other
                    // way around. But I am tired so I leave that for tomorrow
  {

    switch(op)
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

        default:
          halt = 1;
      }
  }
  return;
}

int main(int argc, char **argv)
{
  // Reading the instrustions
  int i = 0, j = 1, len, num, insts[MAX_CODE_LENGTH];
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

    insts[i++] = num;
    fscanf(fp, "%d", &num);
  }
  // Prints last value scanned
  printf("%d\n", num);

  printf("\n\nContents of insts array after transfer:\n");
  for (i = 0; i < j; i++)
  {
    printf("%d\n", insts[i]); // I guess the last value in the array is garbage?
  }

  fetchCycle(insts, j);

  fclose(fp);
  return 0;
}
