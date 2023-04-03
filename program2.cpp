#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "util.h"
#include "parser.h"

#include "program2.h"
#include "programFile.h"

using namespace std;

// Loads the program.
void LoadProgram(char *programFileName) {

	//printf("Entered Load Program\n");

	ProgramFile program;	// Current program
	TokenList *tokenList;	// List of tokens
	Parser *newParser = new Parser();	//Parser Object

	tokenList = program.LoadFile(programFileName);

	//TEMPORARY: PRINT OUT THE TOKENS
	if(tokenList != nullptr)
	{
		if (tokenList->GetNumberOfTokens() != 0)
		{
			for (int i = 0; i < tokenList->GetNumberOfTokens(); i++)
			{
				Token *newTok = tokenList->GetToken(i);
			}
			newParser->Parse(tokenList);
		}
		else
		{
			printf("SYNTAX ERROR");
			exit(1);
		}
	}
	else
	{
		//Tokenizer Error
		printf("TOKENIZER ERROR");
	}
}