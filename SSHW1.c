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


int main()
{

	//Okay so we will have 2 files, an input and an output
	//One of the outputs should be able to be included in the main, I'm thinking. So that just leaves the last output

	int i;
	FILE *fINPUT; //, fOUTPUT;
	fINPUT = fopen("filename.txt", "r");
	//fOUTPUT = fopen("output.txt", "w");
	//fopen "w" I think that writes an empty file? 

	if(fINPUT != NULL)
	{
		printf("The file was opened successfully.\n");
	}

	else
	{
		printf("Error.\n");
		return 0;
	}

	i=0;

	//collecting input and then printing output #1
	
	printf("Line   OP       R      L      M\n");
	while(!feof(fINPUT))
	{
		printf("%d      ", i);

		fscanf(fINPUT, %d, &filename[i].op);
		printf("%d    ", op); //??????????????????????? how would we print this
		
		fscanf(fINPUT, %d, &filename[i].reg);
		printf("%d    ", &reg);

		fscanf(fINPUT, %d, &filename[i].l);
		printf("%d    ", &l); 

		fscanf(fINPUT, %d, &filename[i].m);
		printf("%d    ", &m);
    
		printf("\n");
		i++;
	}

	fclose(fINPUT);

	return 0;
}

