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

    Declarations(&tokenCounter, tokens);

    ParseBody(&tokenCounter, tokens);

    ListAllPresentTypes();
}

//CONFIDENT: declarations → typeDeclarations variableDeclarations
void Parser::Declarations(int* tokenCounter, TokenList* tokens)
{
    //Type Declarations
    TypeDeclarations(tokenCounter, tokens);

    //Test
    PrintTypeDeclarations();

    //PrintStatementLists

    //Varaible Declarations
    VariableDeclarations(tokenCounter, tokens);

    //Test
    PrintVariableDeclarations();
}

//CONFIDENT: typeDeclarations → TYPE typeDeclarationList | EPSILON
void Parser::TypeDeclarations(int* tokenCounter, TokenList* tokens)
{
    //Type
    //printf("Read: %s \t\tType: %s\n", tokens->GetToken(*tokenCounter)->GetString(), TokenTypeToString(static_cast<int>(tokens->GetToken(*tokenCounter)->GetType())));
    if(tokens->GetToken(*tokenCounter)->GetType() == TokenType::TYPE)
    {
        (*tokenCounter)++;

        //Type Declarations List
        TypeDeclarationsList(tokenCounter, tokens);
    }
    else
    {
        //Not Sure if I should exit here
        cout << "NOT  " << endl;
        exit(1);
    }
}

//CONFIDENT: typeDeclarationList → typeDeclaration { typeDeclaration }
void Parser::TypeDeclarationsList(int* tokenCounter, TokenList* tokens)
{
    while (tokens->GetToken(*tokenCounter)->GetType() != TokenType::VAR &&
           tokens->GetToken(*tokenCounter)->GetType() != TokenType::LeftBRACE)
    {
        //printf("Read: %s \t\tType: %s\n", tokens->GetToken(*tokenCounter)->GetString(), TokenTypeToString(static_cast<int>(tokens->GetToken(*tokenCounter)->GetType())));
        TypeDeclaration(tokenCounter, tokens);
    }
}

//UNSURE: typeDeclaration → idList COLON typeName SEMICOLON
void Parser::TypeDeclaration(int* tokenCounter, TokenList* tokens)
{
    //idList
    vector<Token*>* returnIDs = IDList(tokenCounter, tokens);

    //COLON
    if(tokens->GetToken(*tokenCounter)->GetType() == TokenType::COLON)
    {
        (*tokenCounter)++;

        //TpeName
        TypeName(tokenCounter, tokens);

        for(int i = 0; i < returnIDs->size();i++)
        {
            TypeDescriptor *test = new TypeDescriptor();
            test->typeName = (*returnIDs)[i];
            test->type = tokens->GetToken(*tokenCounter-1);
            typeDescriptors.push_back(test);
        }

        //SEMICOLON
        if(tokens->GetToken(*tokenCounter)->GetType() == TokenType::SEMICOLON)
        {
            //printf("Read: %s \t\tType: %s\n", tokens->GetToken(*tokenCounter)->GetString(), TokenTypeToString(static_cast<int>(tokens->GetToken(*tokenCounter)->GetType())));
            (*tokenCounter)++;
        }
    }
}
//typeName → BOOLEAN | INT | LONG | REAL | STRING | ID
void Parser::TypeName(int* tokenCounter, TokenList* tokens)
{
    Token* newToken = tokens->GetToken(*tokenCounter);
    if(newToken->GetType() == TokenType::BOOLEAN
        || newToken->GetType() == TokenType::INT
        || newToken->GetType() == TokenType::LONG
        || newToken->GetType() == TokenType::REAL
        || newToken->GetType() == TokenType::STRING
        || newToken->GetType() == TokenType::ID)
    {
        //printf("Read: %s \t\tType: %s\n", tokens->GetToken(*tokenCounter)->GetString(), TokenTypeToString(static_cast<int>(tokens->GetToken(*tokenCounter)->GetType())));
        (*tokenCounter)++;
    }
}
//CONFIDENT: variableDeclarations → VAR variableDeclarationList | EPSILON
void Parser::VariableDeclarations(int* tokenCounter, TokenList* tokens)
{
    //VAR
    //printf("Read: %s \t\tType: %s\n", tokens->GetToken(*tokenCounter)->GetString(), TokenTypeToString(static_cast<int>(tokens->GetToken(*tokenCounter)->GetType())));
    if(tokens->GetToken(*tokenCounter)->GetType() == TokenType::VAR)
    {
        (*tokenCounter)++;

        //Variable Declarations List
        VariableDeclarationList(tokenCounter, tokens);
    }
    else
        cout << "OF" << endl;
}

//variableDeclarationList → variableDeclaration { variableDeclaration }
void Parser::VariableDeclarationList(int* tokenCounter, TokenList* tokens)
{
    while (tokens->GetToken(*tokenCounter)->GetType() != TokenType::LeftBRACE)
    {
        //printf("Read: %s \t\tType: %s\n", tokens->GetToken(*tokenCounter)->GetString(), TokenTypeToString(static_cast<int>(tokens->GetToken(*tokenCounter)->GetType())));
        VariableDeclaration(tokenCounter, tokens);
    }
}

//CONFIDENT: variableDeclaration → idList COLON typeName SEMICOLON
void Parser::VariableDeclaration(int* tokenCounter, TokenList* tokens)
{
    //idList
    vector<Token*>* returnIDs = IDList(tokenCounter, tokens);

    //COLON
    //printf("Read: %s \t\tType: %s\n", tokens->GetToken(*tokenCounter)->GetString(), TokenTypeToString(static_cast<int>(tokens->GetToken(*tokenCounter)->GetType())));
    if(tokens->GetToken(*tokenCounter)->GetType() == TokenType::COLON)
    {
        (*tokenCounter)++;

        //TpeName
        TypeName(tokenCounter, tokens);

        for(int i = 0; i < returnIDs->size();i++)
        {
            VariableDescriptor *test = new VariableDescriptor();
            test->variableName = (*returnIDs)[i];
            test->type = tokens->GetToken(*tokenCounter-1);
            variableDescriptors.push_back(test);
        }


        //SEMICOLON
        if(tokens->GetToken(*tokenCounter)->GetType() == TokenType::SEMICOLON)
        {
            (*tokenCounter)++;
        }
        else
        {
                    cout << ":" << endl;

            exit(1);
        }
    }
    else
    {
                cout << "E" << endl;

        exit(1);
    }
}

//UNSUREL idList → ID { COMMA ID }
vector<Token*>* Parser::IDList(int* tokenCounter, TokenList* tokens)
{    
    vector<Token*>* resultTokens = new vector<Token*>();
    Token *newToken = tokens->GetToken(*tokenCounter);

    while (newToken->GetType() == TokenType::ID || newToken->GetType() == TokenType::COMMA)
    {
        if(tokens->GetToken(*tokenCounter)->GetType() != TokenType::COMMA)
        {
            resultTokens->push_back(tokens->GetToken(*tokenCounter));
        }

        (*tokenCounter)++;
        newToken = tokens->GetToken(*tokenCounter);
    }

    return resultTokens;
}

//body → LeftBRACE statementList RightBRACE
void Parser::ParseBody(int* tokenCounter, TokenList* tokens)
{
    //printf("Entered Parse Body\n");

    //LeftBRACE
    //printf("Read: %s \t\tType: %s\n", tokens->GetToken(*tokenCounter)->GetString(), TokenTypeToString(static_cast<int>(tokens->GetToken(*tokenCounter)->GetType())));
    if(tokens->GetToken(*tokenCounter)->GetType() == TokenType::LeftBRACE)
    {
        (*tokenCounter)++;

        //StatementList
        StatementList(tokenCounter, tokens);

        //RightBrace
        //printf("Read: %s \t\tType: %s\n", tokens->GetToken(*tokenCounter)->GetString(), TokenTypeToString(static_cast<int>(tokens->GetToken(*tokenCounter)->GetType())));
        if(tokens->GetToken(*tokenCounter)->GetType() == TokenType::RightBRACE)
        {
            (*tokenCounter)++;
        }
    }
	//printf("Exited Parse Body\n");
}


//statementList → statement { statement }
void Parser::StatementList(int* tokenCounter, TokenList* tokens)
{
    //printf("Entered Statement List\n");

    //RightBracket
    while (tokens->GetToken(*tokenCounter)->GetType() != TokenType::RightBRACE)
    {
        //printf("Read: %s \t\tType: %s\n", tokens->GetToken(*tokenCounter)->GetString(), TokenTypeToString(static_cast<int>(tokens->GetToken(*tokenCounter)->GetType())));
        Statement(tokenCounter, tokens);
    }

    //printf("Exited Statement List\n");
}

//statement → whileStatement | assignStatement | doStatement
void Parser::Statement(int* tokenCounter, TokenList* tokens)
{
    //printf("Entered Statement\n");

    //While Statement
    if(tokens->GetToken(*tokenCounter)->GetType() == TokenType::WHILE)
    {
        WhileStatement(tokenCounter, tokens);
    }

    //Assign Statement
    else if(tokens->GetToken(*tokenCounter)->GetType() == TokenType::ID)
    {
        AssignStatement(tokenCounter, tokens);
    }

    //Do Statement
    else if(tokens->GetToken(*tokenCounter)->GetType() == TokenType::DO)
    {
        DoStatement(tokenCounter, tokens);
    }
    else
    {

    }
    //printf("Exited Statement\n");
}

//whileStatement → WHILE conditional body
void Parser::WhileStatement(int* tokenCounter, TokenList* tokens)
{
    //printf("Entered While Statement\n");

    //WHILE
    //printf("Read: %s \t\tType: %s\n", tokens->GetToken(*tokenCounter)->GetString(), TokenTypeToString(static_cast<int>(tokens->GetToken(*tokenCounter)->GetType())));
    if(tokens->GetToken(*tokenCounter)->GetType() == TokenType::WHILE)
    {
        (*tokenCounter)++;

        //Condittional
        Conditional(tokenCounter, tokens);

        //Body
        ParseBody(tokenCounter, tokens);
    }

    //printf("Exited While Statement\n");
}

//assignStatement → ID EQUAL expression SEMICOLON
void Parser::AssignStatement(int* tokenCounter, TokenList* tokens)
{
    //printf("Entered Assign Statement\n");

    //ID
    //printf("Read: %s \t\tType: %s\n", tokens->GetToken(*tokenCounter)->GetString(), TokenTypeToString(static_cast<int>(tokens->GetToken(*tokenCounter)->GetType())));
    if(tokens->GetToken(*tokenCounter)->GetType() == TokenType::ID)
    {
        (*tokenCounter)++;

        //EQUAL
        //printf("Read: %s \t\tType: %s\n", tokens->GetToken(*tokenCounter)->GetString(), TokenTypeToString(static_cast<int>(tokens->GetToken(*tokenCounter)->GetType())));
        if(tokens->GetToken(*tokenCounter)->GetType() == TokenType::EQUAL)
        {
            (*tokenCounter)++;

            //Expression
            Expression(tokenCounter, tokens);

            //SEMICOLON
            //printf("Read: %s \t\tType: %s\n", tokens->GetToken(*tokenCounter)->GetString(), TokenTypeToString(static_cast<int>(tokens->GetToken(*tokenCounter)->GetType())));
            if(tokens->GetToken(*tokenCounter)->GetType() == TokenType::SEMICOLON)
            {
                (*tokenCounter)++;
            }
        }
    }

    //printf("Exited Assign Statement\n");
}

//doStatement → DO body WHILE conditional SEMICOLON
void Parser::DoStatement(int* tokenCounter, TokenList* tokens)
{
    //printf("Entered Do Statement\n");

    //DO
    //printf("Read: %s \t\tType: %s\n", tokens->GetToken(*tokenCounter)->GetString(), TokenTypeToString(static_cast<int>(tokens->GetToken(*tokenCounter)->GetType())));
    if(tokens->GetToken(*tokenCounter)->GetType() == TokenType::DO)
    {
        (*tokenCounter)++;

        //Body
        ParseBody(tokenCounter, tokens);

        //WHILE
        //printf("Read: %s \t\tType: %s\n", tokens->GetToken(*tokenCounter)->GetString(), TokenTypeToString(static_cast<int>(tokens->GetToken(*tokenCounter)->GetType())));
        if(tokens->GetToken(*tokenCounter)->GetType() == TokenType::WHILE)
        {
            (*tokenCounter)++;

            //Conditional
            Conditional(tokenCounter, tokens);

            //SEMICOLON
            //printf("Read: %s \t\tType: %s\n", tokens->GetToken(*tokenCounter)->GetString(), TokenTypeToString(static_cast<int>(tokens->GetToken(*tokenCounter)->GetType())));
            if(tokens->GetToken(*tokenCounter)->GetType() == TokenType::SEMICOLON)
            {
                (*tokenCounter)++;
            }
        }
    }

    //printf("Exited Do Statement\n");
}

//expression → term PLUS expression | term MINUS expression | term
void Parser::Expression(int* tokenCounter, TokenList* tokens)
{
    //printf("Entered Expression\n");

    //Term
    Term(tokenCounter, tokens);

    if(tokens->GetToken(*tokenCounter)->GetType() == TokenType::PLUS
    || tokens->GetToken(*tokenCounter)->GetType() == TokenType::MINUS)
    {
        //PLUS or MINUS
        //printf("Read: %s \t\tType: %s\n", tokens->GetToken(*tokenCounter)->GetString(), TokenTypeToString(static_cast<int>(tokens->GetToken(*tokenCounter)->GetType())));
        (*tokenCounter)++;

        Expression(tokenCounter, tokens);
    }

    //printf("Exited Expression\n");
}

//term → factor MULT term | factor DIV term | factor
void Parser::Term(int* tokenCounter, TokenList* tokens)
{
    //printf("Entered Term\n");

    //Factor
    Factor(tokenCounter, tokens);
    
    if(tokens->GetToken(*tokenCounter)->GetType() == TokenType::MULT
    || tokens->GetToken(*tokenCounter)->GetType() == TokenType::DIV)
    {
        //MULT or DIV
        //printf("Read: %s \t\tType: %s\n", tokens->GetToken(*tokenCounter)->GetString(), TokenTypeToString(static_cast<int>(tokens->GetToken(*tokenCounter)->GetType())));
        (*tokenCounter)++;

        Term(tokenCounter, tokens);
    }

    //printf("Exited Term\n");
}

//factor → LeftPAREN expression RightPAREN | ID | NUM | RealNUM
void Parser::Factor(int* tokenCounter, TokenList* tokens)
{
    //printf("Entered Factor\n");

    //LeftPAREN
    //printf("Read: %s \t\tType: %s\n", tokens->GetToken(*tokenCounter)->GetString(), TokenTypeToString(static_cast<int>(tokens->GetToken(*tokenCounter)->GetType())));
    if(tokens->GetToken(*tokenCounter)->GetType() == TokenType::LeftPAREN)
    {
        (*tokenCounter)++;

        Expression(tokenCounter, tokens);

        //printf("Read: %s \t\tType: %s\n", tokens->GetToken(*tokenCounter)->GetString(), TokenTypeToString(static_cast<int>(tokens->GetToken(*tokenCounter)->GetType())));
        if(tokens->GetToken(*tokenCounter)->GetType() == TokenType::RightPAREN)
        {
            (*tokenCounter)++;
        }
    }
    else if(tokens->GetToken(*tokenCounter)->GetType() == TokenType::ID
         || tokens->GetToken(*tokenCounter)->GetType() == TokenType::NUM
         || tokens->GetToken(*tokenCounter)->GetType() == TokenType::RealNUM)
    {
        (*tokenCounter)++;
    }

    //printf("Exited Factor\n");
}

//conditional → ID | primary relationalOperator primary
void Parser::Conditional(int* tokenCounter, TokenList* tokens)
{
    //printf("Entered Conditional\n");

    //ID
    //printf("Read: %s \t\tType: %s\n", tokens->GetToken(*tokenCounter)->GetString(), TokenTypeToString(static_cast<int>(tokens->GetToken(*tokenCounter)->GetType())));
    if(tokens->GetToken(*tokenCounter)->GetType() == TokenType::COLON)
    {
        (*tokenCounter)++;
    }
    else
    {
        //Primary
        Primary(tokenCounter, tokens);

        //RelationalOperator
        RelationalOperator(tokenCounter, tokens);

        //Primary
        Primary(tokenCounter, tokens);
    }

    //printf("Exited Conditional\n");
}

//primary → ID | NUM | RealNUM
void Parser::Primary(int* tokenCounter, TokenList* tokens)
{
    //printf("Entered Primary\n");

    Token* newToken = tokens->GetToken(*tokenCounter);
    if(newToken->GetType() == TokenType::ID
        || newToken->GetType() == TokenType::NUM
        || newToken->GetType() == TokenType::RealNUM)
    {
        //printf("Read: %s \t\tType: %s\n", tokens->GetToken(*tokenCounter)->GetString(), TokenTypeToString(static_cast<int>(tokens->GetToken(*tokenCounter)->GetType())));
        (*tokenCounter)++;
    }

    //printf("Exited Primary\n");
}

//relationalOperator → EQUAL | NotEQUAL | GREATER | GTEQ | LESS | LTEQ
void Parser::RelationalOperator(int* tokenCounter, TokenList* tokens)
{
    //printf("Entered Relational Operator\n");

    Token* newToken = tokens->GetToken(*tokenCounter);
    if(newToken->GetType() == TokenType::EQUAL
        || newToken->GetType() == TokenType::NotEQUAL
        || newToken->GetType() == TokenType::GREATER
        || newToken->GetType() == TokenType::GtEQ
        || newToken->GetType() == TokenType::LESS
        || newToken->GetType() == TokenType::LtEQ)
    {
        //printf("Read: %s \t\tType: %s\n", tokens->GetToken(*tokenCounter)->GetString(), TokenTypeToString(static_cast<int>(tokens->GetToken(*tokenCounter)->GetType())));
        (*tokenCounter)++;
    }

    //printf("Exited Relational Operator\n");
}

void Parser::PrintTypeDeclarations()
{
    //printf("Entered PrintTypeDeclarations\n");
    for(int i = 0; i < typeDescriptors.size(); i++)
    {
        TypeDescriptor *typeDescriptor = typeDescriptors[i];
        printf("Type Name: %s\tType Type: %s\n", typeDescriptor->typeName->GetString(), typeDescriptor->type->GetString());
        //printf("Type Name: %s\n", typeDescriptor->typeName->GetString());
    }
    //printf("Exited PrintTypeDeclarations\n");
}

void Parser::PrintVariableDeclarations()
{
    //printf("Entered PrintVariableDeclarations\n");
    for(int i = 0; i < variableDescriptors.size(); i++)
    {
        VariableDescriptor *variableDescriptor = variableDescriptors[i];
        //printf("Read: %s \t\tType: %s\n", tokens->GetToken(*tokenCounter)->GetString(), TokenTypeToString(static_cast<int>(tokens->GetToken(*tokenCounter)->GetType())));
        printf("Variable Name: %s\tVariable Type: %s\n", variableDescriptor->variableName->GetString(), variableDescriptor->type->GetString());
    }
    //printf("Exited PrintTypeDeclarations\n");
}

void Parser::ListAllPresentTypes()
{
    printf("Entered List All Present Types\n");

	for(vector<TypeDescriptor*>::iterator it = typeDescriptors.begin(); it != typeDescriptors.end(); it++)
    {
        //CheckType((*it)->type->GetType());

        // {
    if((*it)->type->GetType() == TokenType::INT)
    {
        printf("%s",(*it)->typeName->GetString());
    }
    else if((*it)->type->GetType() == TokenType::BOOLEAN)
    {
    }

    //printf("BOOLEAN # \nINT #\nLONG #\nREAL #\nSTRING #\n");
}

// vector<Token*> Parser:CheckType(TokenType tokenType)
// {
//     if(tokenType == TokenType::INT)
//     {
//         intTokens->push_back(tokenType);
//     }
//     else if(tokenType == TokenType::BOOLEAN)
//     {

//     }
//     else
//     {
//         CheckType();
//     }
//     return 
// }
}


void Parser::CheckDuplicateErrors()
{
// 1. Explicit type redeclared explicitly - A type is declared explicitly twice.
// 2. Implicit type redeclared explicitly - A type is declared explicitly after being declared
// implicitly.
// 3. Programmer-defined type redeclared as variable - A name is declared as both a type and a
// variable.
// 4. Programmer-defined type used as variable - A name is declared as a type, then used as a
// variable.
// 5. Variable declared more than once - A variable is declared twice.
// 6. Variable used as a type - A variable is used as a type in a variable declaration.
// Note that implicit declarations can not occur after an explicit declaration, as this would be a use,
// not a declaration. Also, if one of the built-in types is redeclared as a type, declared as a variable,

}

