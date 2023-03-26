#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "util.h"
#include "token.h"
#include "tokenList.h"
#include "tokenType.h"

using namespace std;

class Parser
{
    public:

        void Parse(TokenList* tokens);

        //Working On
        //bool TypeName(const char* token);
        //bool Conditional(const char* token);
        //bool RelationalOperator(const char* token);
        //bool Primary(const char* token);

    private:
        void Declarations(int* tokenCounter, TokenList* tokens);
        void TypeDeclarations(int* tokenCounter, TokenList* tokens);
        void TypeDeclarationsList(int* tokenCounter, TokenList* tokens);
        void TypeDeclaration(int* tokenCounter, TokenList* tokens);
        void TypeName(int* tokenCounter, TokenList* tokens);
        void VariableDeclarations(int* tokenCounter, TokenList* tokens);
        void VariableDeclarationList(int* tokenCounter, TokenList* tokens);
        void VariableDeclaration(int* tokenCounter, TokenList* tokens);
        vector<Token*>* IDList(int* tokenCounter, TokenList* tokens);


        //declarations → typeDeclarations variableDeclarations
        //typeDeclarations → TYPE typeDeclarationList | EPSILON
        //typeDeclarationList → typeDeclaration { typeDeclaration }
        //typeDeclaration → idList COLON typeName SEMICOLON
        //typeName → BOOLEAN | INT | LONG | REAL | STRING | ID
        //variableDeclarations → VAR variableDeclarationList | EPSILON
        //variableDeclarationList → variableDeclaration { variableDeclaration }
        //variableDeclaration → idList COLON typeName SEMICOLON
        //idList → ID { COMMA ID }


};
#endif
