#define MAX_ARRAY_SIZE 65536
#include <stdio.h>
#include <string.h>
#include <stack.h>

// Author: Yair
// Date: 03-04-18
// Compiler and Interpeter for programming language brainfuck or in the future with some changes a new programming language


// GLOBAL VARIABLES
char array[MAX_ARRAY_SIZE] = { 0 };
char *ptr = array;
// This is the file for		
FILE* mainCodeFile = NULL;
char* mainCodeFileName = NULL;
// TODO MAYBE CHANGE THIS VARIABLE TO BE NOT GLOBAL BUT INSIDE THE RELEVANT FUNCTIONS
FILE* outputCCodeFile = NULL;
char helpText[] = "This is a Compiler and Interpeter for programming language brainfuck or in the future with some changes a new programming language\
\
Usage:\
-h		show this help text and version and usage of this program\
-c [filename]		compile this file to c file\
-f [filename]		interperet this file containing code\
-m [number of bytes]		set max array memory, used in big program to set more memory";

// multi line string literal using \ 
// example:
// "hey \
// hello"



// TODO ADD STATE MACHINE HERE, MAYBE VIA HASH MAP OR TWO ORDERER ARRAYS
//struct state
//{
//	char command;
//	void (*func)(void);
//};


/*
TODO LIST

- create functions prototypes and beautify code
- better use in cli options, argc and argv
- add help and version and description of the program in UI/UX
- add looping commands [] mechanism and infrastructure, maybe use index variable for last [ bracket, maybe better using stack for many loops
- add input cli option for recieving the output file name, for now use same file name but with different file ending

Extending the language:
- add file and code import/using/include to a program using a new specific char command.
- add commenting of lines of code
*/


/*
NOTES

- use only fread and fwrite for files, maybe use text writing in compiling the file
*/



// Programming language command functions here

/*
>
increment the data pointer, go to next cell
*/
void commandRightArrow()
{
	++ptr;
}

/*
<
decrement the data pointer, go to previous cell
*/
void commandLeftArrow()
{
	--ptr;
}

/*
+
increment the data in the data pointer
*/
void commandPlus()
{
	++*ptr;
}

/*
-
decrement the data in the data pointer
*/
void commandMinus()
{
	--*ptr;
}

/*
.
I/O function, read one byte from input to current cell
TODO MAYBE - HAVE OPTION FOR HAVING INPUT BYTE ARRAY FROM USER INPUT OR SPECIFIC STRING THAT IS ENTERED OR READ FROM FILE
For now read from user input
*/
void commandDot()
{
	putchar(*ptr);
}

/*
,
I/O function, write one byte from input to current cell
*/
void commandComma()
{
	*ptr = getchar();
}
// TODO IMPORTANT - ADD LOOPING MECHANISM AND INFRASTRUCTURE
// TODO IMPORTANT ADD BRACKETS

/*
[
loop function,
*/
void commandLeftBracket()
{

}

/*
]
loop function,
*/
void commandRightBracket()
{

}


// handling a char command function here
// TODO LOW - IMPROVE THIS FUNCTION BY USING A STATE MACHINE OR SOMETHING SIMILAR INSTEAD OF A LOT OF IF STATEMENTS
void handleCharCommand(char charCommand)
{
	if (charCommand == '+')
	{
		commandPlus();
	}
	if (charCommand == '-')
	{
		commandMinus();
	}
	if (charCommand == '>')
	{
		commandRightArrow();
	}
	if (charCommand == '<')
	{
		commandLeftArrow();
	}
	if (charCommand == ',')
	{
		commandComma();
	}
	if (charCommand == '.')
	{
		commandDot();
	}
	if (charCommand == '[')
	{
		commandLeftBracket();
	}
	if (charCommand == ']')
	{
		commandRightBracket();
	}
}



// replacing a char command function here
// used for compiling to a C file
// TODO LOW - IMPROVE THIS FUNCTION BY USING A STATE MACHINE OR SOMETHING SIMILAR INSTEAD OF A LOT OF IF STATEMENTS
// TODO LOW - ALSO CHECK IF IT WORKS RIGHT AND GOOD OR IT CAN BE IMPROVED
void writeCharaterReplacementMacro(char charCommand)
{
	if (charCommand == '+')
	{
		fprintf_s(outputCCodeFile, "++*ptr;\n");
	}
	if (charCommand == '-')
	{
		fprintf_s(outputCCodeFile, "--*ptr;\n");
	}
	if (charCommand == '>')
	{
		fprintf_s(outputCCodeFile, "++ptr;\n");
	}
	if (charCommand == '<')
	{
		fprintf_s(outputCCodeFile, "--ptr;\n");
	}
	if (charCommand == ',')
	{
		fprintf_s(outputCCodeFile, "*ptr=getchar();\n");
	}
	if (charCommand == '.')
	{
		fprintf_s(outputCCodeFile, "putchar(*ptr);\n");
	}
	if (charCommand == '[')
	{
		fprintf_s(outputCCodeFile, "while (*ptr) {\n");
	}
	if (charCommand == ']')
	{
		fprintf_s(outputCCodeFile, "};\n");
	}
}


/*
need to decide on char command for this function
new command and function, file and code import/using/include
TODO LOW - need to implement this
*/
void commandImportFile()
{
	puts("NOT IMPLEMENTED YET.");
}








// Program modes here
// assume in every program mode that if the main code file is needed then it is already open
// TODO IMPLEMENT ALL THE PROGRAM MODES
int compileMode()
{
	// variables for writing to output file
	char outputFileName[256] = { "outputFileName" };
	// variables for reading from input file
	char curCharCommand;
	int readStatus;
	// maybe check this strncpy for security look what it does to string at data level
	// TODO MAKE A SPECIFIC FILENAME AND NOT A CONST HARD-CODED ONE
	// strncpy_s(outputFileName, 252, mainCodeFileName, 252);
	// adding .c to the end of the file name
	outputFileName[strlen(outputFileName)] = '.';
	outputFileName[strlen(outputFileName)] = 'c';
	// creating, opening and overriting the file
	fopen_s(&outputCCodeFile, outputFileName, "wb");


	readStatus = fread(&curCharCommand, 1, 1, mainCodeFile);
	// read status should be the amount of bytes that we read, should always be 1 unless we finished reading or some error
	while (readStatus == 1)
	{
		// writing the replacement macro of the char command that we read
		writeCharaterReplacementMacro(curCharCommand);
		// reading another char command, in order to continue the loop
		readStatus = fread(&curCharCommand, 1, 1, mainCodeFile);
	}

	fclose(outputCCodeFile);

	return 0;
}
// TODO HIGH IMPLEMENT THIS IN THE BEST WAY
int interpeterMode()
{
	char curCharCommand;
	int readStatus;
	readStatus = fread(&curCharCommand, 1, 1, mainCodeFile);
	// read status should be the amount of bytes that we read, should always be 1 unless we finished reading or some error
	while (readStatus == 1)
	{
		handleCharCommand(curCharCommand);
		readStatus = fread(&curCharCommand, 1, 1, mainCodeFile);
	}
	return 0;
}
// TODO IN PRIORITY LOW - ADD THIS PROGRAM MODE
int interactiveMode()
{
	mainCodeFile = stdin;
	return interpeterMode();
}
int printHelp()
{

	puts(helpText);
	return 0;
}



int main(int argc, char* argv[])
{

	// TODO ADD USE AND HANDLING BETTER WITH THE OPTIONS, ARGC AND ARGV
	/*
	analyze which option the user want to use:
	- compile to c file or executable file ( option -c )
	- interperet from file containing code ( option -f )
	- interactive mode, CLI running code ( no option or -i), maybe not needed or low priority
	- show help and version and usage of this program ( option -h ), needed!
	- set max memory ( option -m [number of bytes] )
	*/
	// TODO MAYBE - add a state machine to save the if statements
	int(*ptrProgramMode)() = NULL;
	int exitCode = 0; // default program exit code is 0 zero - meaning everything is good
	if (argc == 1)
	{
		ptrProgramMode = interactiveMode;
	}
	else
	{
		if (argc == 2)
		{
			// we are for -h or -i option or filename without any option so we should treat it as -f option
			if (argv[1][0] == '-' && argv[1][1] == 'h') {
				ptrProgramMode = printHelp;
			}
			else {
				if (argv[1][0] == '-' && argv[1][1] == 'i') {
					ptrProgramMode = interactiveMode;
				}
				else
				{
					fopen_s(&mainCodeFile, argv[1], "rb");
					mainCodeFileName = argv[1];
					ptrProgramMode = interpeterMode;
				}
			}
		}
		else
		{
			// we are here if we are -f or -c options
			// opening main code file for interperet or compile
			if (argc == 3)
			{
				if (argv[1][0] == '-' && argv[1][1] == 'f')
				{
					fopen_s(&mainCodeFile, argv[2], "rb");
					mainCodeFileName = argv[2];
					ptrProgramMode = interpeterMode;
				}
				else
				{
					if (argv[1][0] == '-' && argv[1][1] == 'c')
					{
						// TODO ADD INPUT CLI OPTION FOR RECIEVING THE OUTPUT FILE NAME, FOR NOW USE SAME FILE NAME BUT WITH DIFFERENT FILE ENDING
						fopen_s(&mainCodeFile, argv[2], "rb");
						mainCodeFileName = argv[2];
						ptrProgramMode = compileMode;
					}
				}
			}
		}
	}
	if (ptrProgramMode == NULL)
	{
		// we are here if no option is correct so we should return with exit code 1, meaning Error occured
		ptrProgramMode = printHelp;
	}
	// MAIN  - run the program in the specific program mode
	// also getting the exit code from running in the program mode
	exitCode = ptrProgramMode();
	// figure out where to put this code
	if (mainCodeFile != NULL)
	{
		fclose(mainCodeFile);
	}

	return exitCode;

}
