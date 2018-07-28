#define MAX_ARRAY_SIZE 65536
#include <stdio.h>
#include <string.h>

// Author: Yair
// Date: 03-04-18
// C Code Template for the Compiler, in the future add here some changes and features to create a new programming language


// GLOBAL VARIABLES
char array[MAX_ARRAY_SIZE] = { 0 };
char *ptr = array;

void writeCharToArrayAndIncrementPointer(char c)
{
	*ptr = c;
	ptr++;
}
// TODO MAYBE ADD HERE ARGC AND ARGV
int main(int argc,char** argv)
{

	// argc and argv variables
	// the argc is stores at the first cell and the argv's stores in the cells afterwards, each of ends with zero byte
	{
		int i;
		char* ptrArgvCharCurrent;
		writeCharToArrayAndIncrementPointer(argc);

		for (i = 0; i < argc; i++) {
			// now we should write the argv strings
			ptrArgvCharCurrent = argv[i];
			while (ptrArgvCharCurrent)
			{
				// writing it to array stream
				writeCharToArrayAndIncrementPointer(*ptrArgvCharCurrent);
				// incrementing in order to point to the char in the argv string
				ptrArgvCharCurrent++;
			}
			// we reached end of string at argv[i], now we should write the null-terminator, the 0 byte
			writeCharToArrayAndIncrementPointer(0);
		}
		// going back to the start of the array
		ptr = array;
	}

	// assigning the brainfuck code here
	%s
	// exit code is based on the current cell data
	return *ptr;
}