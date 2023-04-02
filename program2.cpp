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

			if(newTok != nullptr)
			{
				//TEMPORARY: PRINT OUT READ< TYPE< INT
				//printf("Read: %s ", newTok->GetString());
				//printf("\t\tType: %s\n", TokenTypeToString(static_cast<int>(newTok->GetType())));
			}
			else
			{
				//std::cout << "Null token pointer" << std::endl;
			}
		}

		//printf("END OF TEST\n\n\n");
		newParser->Parse(tokenList);
		//printf("Program loaded successfully.\n");
	}
	else
	{
		//Tokenizer Error
		std::cout << "TOKENIZER ERROR";
	}
}