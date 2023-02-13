#include <stdio.h>
#define PROGRAMLEN 10 // MAX number of instructions 

int program[PROGRAMLEN];

/*
Load: this method reads a .txt file line by line and stores the lines (instructions) in an array 
*/
int load (char* fileName)
{

	FILE *instructionsFile = fopen(fileName, "r");

	if (instructionsFile == 0)
	{
		fprintf(stderr, "Error: Failed to open %s\n", fileName);
	}

	else
	{
		int i = 0;
		int status = 0;
		while (status != -1){
			status = fscanf(instructionsFile, "%x", &program[i]); // "%x" = hex, fscanf returns -1 when no hex value found
			i++;
		}
		fclose(instructionsFile);
	}

}

int main()
{
	load("data.txt");
}
