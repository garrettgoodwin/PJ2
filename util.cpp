#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "tokenType.h"

#include "util.h"


void PrintError(char *errorType, int errorNumb, int lineNumb)
{
    if(strcmp(errorType, "Tokenizer"))
    {
        printf("TOKENIZER ERROR");
    }
    else if(strcmp(errorType, "Syntax"))
    {
        printf("SYNTAX ERROR");
    }
    else if(strcmp(errorType, "Duplication"))
    {
        printf("DUPLICATION ERROR %d <name>", errorNumb);
    }
    else if(strcmp(errorType, "Type"))
    {
        printf("TYPE MISMATCH %d %d", errorNumb, lineNumb);
    }
    else
    {
        printf("Unrecognized Error");
    }
}


const char* TokenTypeToString(int type)
{
    switch(type)
    {
        case 0:
            return "COLON";
            break;
        case 1:
            return "SEMICOLON";
            break;
        case 2:
            return "COMMA";
            break;
        case 3:
            return "LeftBRACE";
            break;
        case 4:
            return "RightBRACE";
            break;
        case 5:
            return "EQUAL";
            break;
        case 6:
            return "PLUS";
            break;
        case 7:
            return "MINUS";
            break;
        case 8:
            return "MULT";
            break;
        case 9:
            return "DIV";
            break;
        case 10:
            return "LeftPAREN";
            break;
        case 11:
            return "RightPAREN";
            break;
        case 12:
            return "GREATER";
            break;
        case 13:
            return "GtEQ";
            break;
        case 14:
            return "LESS";
            break;
        case 15:
            return "LtEQ";
            break;
        case 16:
            return "NotEQUAL";
            break;
        case 17:
            return "TYPE";
            break;
        case 18:
            return "BOOLEAN";
            break;
        case 19:
            return "INT";
            break;
        case 20:
            return "LONG";
            break;
        case 21:
            return "REAL";
            break;
        case 22:
            return "STRING";
            break;
        case 23:
            return "VAR";
            break;
        case 24:
            return "WHILE";
            break;
        case 25:
            return "DO";
            break;
        case 26:
            return "ID";
            break;
        case 27:
            return "NUM";
            break;
        case 28:
            return "RealNUM";
            break;
        case 29:
            return "INVALID";
            break;
        default:
            return "Unrecognized Type";
    }
}

//void Parse(const char* token)
//{
    // if(IsTypeName(token))
    // {
    //     printf("\nThe token is a typeName\n");
    // }
    // else
    // {
    //     //printf("\nThe token not a typeName\n");
    // }
//}

