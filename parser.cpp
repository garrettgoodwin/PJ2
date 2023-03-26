#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "util.h"
#include "tokenType.h"
#include "tokenList.h"
#include "parser.h"

using namespace std;

void Parser::Parse(TokenList* tokens)
{
    int tokenCounter = 1;

    //cout << "Begin Parser" << endl;
    Declarations(&tokenCounter, tokens);
}

//CONFIDENT: declarations → typeDeclarations variableDeclarations
void Parser::Declarations(int* tokenCounter, TokenList* tokens)
{
    //TEMPORARY PRINT OUT
    //cout << "ENTERED DECLARATION" << endl;

    //Type Declarations
    TypeDeclarations(tokenCounter, tokens);

    //Varaible Declarations
    VariableDeclarations(tokenCounter, tokens);

    //TEMPORARY PRINT OUT
    //cout << "EXITED DECLARATION" << endl;
}

//CONFIDENT: typeDeclarations → TYPE typeDeclarationList | EPSILON
void Parser::TypeDeclarations(int* tokenCounter, TokenList* tokens)
{
    //TEMPORARY PRINT OUT
    //cout << "ENTERED TYPEDECLARATIONS" << endl;

    //Type
    Token *newToken = tokens->GetToken(*tokenCounter);

    //TEMPORARY PRINT OUT
    printf("Read: %s ", newToken->GetString());
	printf("\t\tType: %s\n", TokenTypeToString(static_cast<int>(newToken->GetType())));

    if(newToken->GetType() == TokenType::TYPE)
    {
        (*tokenCounter)++;

        //Type Declarations List
        TypeDeclarationsList(tokenCounter, tokens);
    }
    else
        cout << "NOT OF TYPE: TYPE" << endl;

    //TEMPORARY PRINT OUT
    //cout << "EXITED TYPEDECLARATIONS" << endl;
}

//CONFIDENT: typeDeclarationList → typeDeclaration { typeDeclaration }
void Parser::TypeDeclarationsList(int* tokenCounter, TokenList* tokens)
{
    //TEMPORARY PRINT OUT
    //cout << "ENTERED TYPEDECLARATIONSLIST" << endl;

    Token *newToken = tokens->GetToken(*tokenCounter);

    //TEMPORARY PRINT OUT
    printf("Read: %s ", newToken->GetString());
	printf("\t\tType: %s\n", TokenTypeToString(static_cast<int>(newToken->GetType())));

    while (newToken->GetType() != TokenType::VAR &&
           newToken->GetType() != TokenType::LeftBRACE)
    {
        TypeDeclaration(tokenCounter, tokens);
    }

    //TEMPORARY PRINT OUT
    cout << "EXITED TYPEDECLARATIONSLIST" << endl;
}

//UNSURE: typeDeclaration → idList COLON typeName SEMICOLON
void Parser::TypeDeclaration(int* tokenCounter, TokenList* tokens)
{
    //TEMPORARY PRINT OUT

    //idList
    //ORIGINALLY WAS: IDList(tokenCounter, tokens);
    vector<Token*>* returnIDs = IDList(tokenCounter, tokens);

    //COLON
    Token *newToken = tokens->GetToken(*tokenCounter);

    //printf("Read: %s ", newToken->GetString());
	//printf("\t\tType: %s\n", TokenTypeToString(static_cast<int>(newToken->GetType())));


    if(newToken->GetType() == TokenType::COLON)
    {
        (*tokenCounter)++;

        //TpeName
        TypeName(tokenCounter, tokens);

        //SEMICOLON
        newToken = tokens->GetToken(*tokenCounter);
        if(newToken->GetType() == TokenType::SEMICOLON)
        {
            printf("Read: %s ", newToken->GetString());
		    printf("\t\tType: %s\n", TokenTypeToString(static_cast<int>(newToken->GetType())));
            (*tokenCounter)++;
        }
    }

    //TEMPORARY PRINT OUT
    //cout << "EXITED TYPEDECLARATION" << endl;
}
//typeName → BOOLEAN | INT | LONG | REAL | STRING | ID
void Parser::TypeName(int* tokenCounter, TokenList* tokens)
{
    //TEMPORARY PRINT OUT
    //cout << "ENTERED TYPENAME" << endl;

    Token* newToken = tokens->GetToken(*tokenCounter);
    if(newToken->GetType() == TokenType::BOOLEAN
        || newToken->GetType() == TokenType::INT
        || newToken->GetType() == TokenType::LONG
        || newToken->GetType() == TokenType::REAL
        || newToken->GetType() == TokenType::STRING
        || newToken->GetType() == TokenType::ID)
    {

        //TEMPORARY: PRINT OUT
        printf("Read: %s ", newToken->GetString());
		printf("\t\tType: %s\n", TokenTypeToString(static_cast<int>(newToken->GetType())));

        (*tokenCounter)++;
    }

    //TEMPORARY PRINT OUT
    //cout << "EXITED TYPENAME" << endl;
}
//CONFIDENT: variableDeclarations → VAR variableDeclarationList | EPSILON
void Parser::VariableDeclarations(int* tokenCounter, TokenList* tokens)
{
    //TEMPORARY PRINT OUT
    //cout << "ENTERED VARIABLEDECLARATIONS" << endl;

    //VAR
    Token *newToken = tokens->GetToken(*tokenCounter);

    //TEMPORARY: PRINT OUT
    printf("Read: %s ", newToken->GetString());
	printf("\t\tType: %s\n", TokenTypeToString(static_cast<int>(newToken->GetType())));

    if(newToken->GetType() == TokenType::VAR)
    {
        (*tokenCounter)++;

        //Variable Declarations List
        VariableDeclarationList(tokenCounter, tokens);
    }
    else
        cout << "NOT OF TYPE: VAR" << endl;

    //TEMPORARY PRINT OUT
    //cout << "EXITED VARIABLEDECLARATIONS" << endl;
}

//variableDeclarationList → variableDeclaration { variableDeclaration }
void Parser::VariableDeclarationList(int* tokenCounter, TokenList* tokens)
{
    //TEMPORARY PRINT OUT
    //cout << "ENTERED VARIABLEDECLARATIONLIST" << endl;

    Token *newToken = tokens->GetToken(*tokenCounter);

    //TEMPORARY: PRINT OUT
    printf("Read: %s ", newToken->GetString());
	printf("\t\tType: %s\n", TokenTypeToString(static_cast<int>(newToken->GetType())));

    while (newToken->GetType() != TokenType::LeftBRACE)
    {
        VariableDeclaration(tokenCounter, tokens);
    }

    //TEMPORARY PRINT OUT
    //cout << "EXITED VARIABLEDECLARATIONLIST" << endl;
}

//CONFIDENT: variableDeclaration → idList COLON typeName SEMICOLON
void Parser::VariableDeclaration(int* tokenCounter, TokenList* tokens)
{
    //TEMPORARY PRINT OUT
    //cout << "ENTERED VARIABLEDECLARATION" << endl;

    //idList
    IDList(tokenCounter, tokens);

    //COLON
    Token *newToken = tokens->GetToken(*tokenCounter);

    //TEMPORARY: PRINT OUT
    //printf("Read: %s ", newToken->GetString());
	//printf("\t\tType: %s\n", TokenTypeToString(static_cast<int>(newToken->GetType())));

    if(newToken->GetType() == TokenType::COLON)
    {
        (*tokenCounter)++;

        //TpeName
        TypeName(tokenCounter, tokens);

        //SEMICOLON
        Token *newToken = tokens->GetToken(*tokenCounter);

        //TEMPORARY: PRINT OUT
        //printf("Read: %s ", newToken->GetString());
		//printf("\t\tType: %s\n", TokenTypeToString(static_cast<int>(newToken->GetType())));

        if(newToken->GetType() == TokenType::SEMICOLON)
        {
            (*tokenCounter)++;
        }
    }

    //TEMPORARY PRINT OUT
    //cout << "EXITED VARIABLEDECLARATION" << endl;
}

//UNSUREL idList → ID { COMMA ID }
vector<Token*>* Parser::IDList(int* tokenCounter, TokenList* tokens)
{
    //TEMPORARY PRINT OUT
    //cout << "ENTERED IDLIST" << endl;
    
    vector<Token*>* resultTokens = new vector<Token*>();
    Token *newToken = tokens->GetToken(*tokenCounter);

    //TEMPORARY: PRINT OUT
    printf("Read: %s ", newToken->GetString());
	printf("\t\tType: %s\n", TokenTypeToString(static_cast<int>(newToken->GetType())));

    while (newToken->GetType() == TokenType::ID || newToken->GetType() == TokenType::COMMA)
    {
        if(newToken->GetType() != TokenType::COMMA)
        {
            resultTokens->push_back(newToken);
        }

        (*tokenCounter)++;
        newToken = tokens->GetToken(*tokenCounter);

        //TEMPORARY: PRINT OUT
        //printf("Read: %s ", newToken->GetString());
		//printf("\t\tType: %s\n", TokenTypeToString(static_cast<int>(newToken->GetType())));
    }

    //TEMPORARY PRINT OUT
    //cout << "EXITED IDLIST" << endl;

    return resultTokens;
}

//typeName → BOOLEAN | INT | LONG | REAL | STRING | ID
// bool Parser::TypeName(const char* token)
// {
//     return (strcmp(token, "BOOLEAN") == 0
//             || strcmp(token, "INT") == 0
//             || strcmp(token, "LONG") == 0
//             || strcmp(token, "REAL") == 0
//             || strcmp(token, "STRING") == 0
//             || strcmp(token, "ID") == 0);
// }

//BUILDING BLOCKS
//conditional → ID | primary relationalOperator primary
// bool Parser::Conditional(const char* token)
// {
//     if(strcmp(token, "ID") == 0)
//     {
//         return true;
//     }
//     else if((Primary(token) && RelationalOperator(token) && Primary(token)))
//     {
//         return true;
//     }
//     else
//     {
//         return false;
//     }
// }

// //relationalOperator → EQUAL | NotEQUAL | GREATER | GTEQ | LESS | LTEQ
// bool Parser::RelationalOperator(const char* token)
// {
//     return (strcmp(token, "EQUAL") == 0
//             || strcmp(token, "NotEQUAL") == 0
//             || strcmp(token, "GREATER") == 0
//             || strcmp(token, "GTEQ") == 0
//             || strcmp(token, "LESS") == 0
//             || strcmp(token, "LTEQ") == 0);
// }

// //primary → ID | NUM | RealNUM
// bool Parser::Primary(const char* token)
// {
//     return (strcmp(token, "ID") == 0
//             || strcmp(token, "NUM") == 0
//             || strcmp(token, "RealNUM") == 0);
// }


// Token* GetNextToken()
// {
// 	return tokenList->GetToken(tokenCounter++);
// }
