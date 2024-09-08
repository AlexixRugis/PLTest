#include "LexerToken.h"

std::string ToString(LexerTokenType type)
{
    switch (type)
    {
    case LexerTokenType::NUM: return "LexerTokenType::NUM";
    case LexerTokenType::ID: return "LexerTokenType::ID";
    case LexerTokenType::STRING: return "LexerTokenType::STRING";
    case LexerTokenType::PRINT: return "LexerTokenType::PRINT";
    case LexerTokenType::IF: return "LexerTokenType::IF";
    case LexerTokenType::ELSE: return "LexerTokenType::ELSE";
    case LexerTokenType::WHILE: return "LexerTokenType::WHILE";
    case LexerTokenType::LBRA: return "LexerTokenType::LBRA";
    case LexerTokenType::RBRA: return "LexerTokenType::RBRA";
    case LexerTokenType::LPAR: return "LexerTokenType::LPAR";
    case LexerTokenType::RPAR: return "LexerTokenType::RPAR";
    case LexerTokenType::INCREMENT: return "LexerTokenType::INCREMENT";
    case LexerTokenType::DECREMENT: return "LexerTokenType::DECREMENT";
    case LexerTokenType::PLUS: return "LexerTokenType::PLUS";
    case LexerTokenType::MINUS: return "LexerTokenType::MINUS";
    case LexerTokenType::MULT: return "LexerTokenType::MULT";
    case LexerTokenType::DIV: return "LexerTokenType::DIV";
    case LexerTokenType::LESS: return "LexerTokenType::LESS";
    case LexerTokenType::LESSEQUAL: return "LexerTokenType::LESSEQUAL";
    case LexerTokenType::GREATER: return "LexerTokenType::GREATER";
    case LexerTokenType::GREATEREQUAL: return "LexerTokenType::GREATEREQUAL";
    case LexerTokenType::ASSIGN: return "LexerTokenType::ASSIGN";
    case LexerTokenType::EQUAL: return "LexerTokenType::EQUAL";
    case LexerTokenType::NOTEQUAL: return "LexerTokenType::NOTEQUAL";
    case LexerTokenType::SEMICOLON: return "LexerTokenType::SEMICOLON";
    case LexerTokenType::ENDOFFILE: return "LexerTokenType::ENDOFFILE";
    default: return "UNKNOWN";
    }
}