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
	ProgramFile program;	// Current program
	TokenList *tokenList;	// List of tokens
	Parser *newParser = new Parser();	//Parser Object

	tokenList = program.LoadFile(programFileName);

	//TEMPORARY: PRINT OUT THE TOKENS
	if(tokenList != nullptr)
	{
		for(int i = 0; i < tokenList->GetNumberOfTokens(); i++)
		{
			Token* newTok =  tokenList->GetToken(i);

			// if(newTok == nullptr)
			// {
			// 	printf("TOKENIZER ERROR");
			// }
		}
		newParser->Parse(tokenList);
	}
	else
	{
		//Tokenizer Error
		printf("TOKENIZER ERROR");
	}
}