#pragma once
#include <string>

enum class LexerTokenType
{
    NUM, ID, STRING, PRINT, IF, ELSE, WHILE, LBRA, RBRA, LPAR, RPAR, PLUS, MINUS, MULT, DIV, LESS, \
    EQUAL, SEMICOLON, ENDOFFILE
};

std::string ToString(LexerTokenType type);

class LexerToken
{
public: 
    LexerToken(LexerTokenType type, const std::string& value) : m_Type(type), m_Value(value) { }
    
    LexerTokenType Type() const { return m_Type; }
    std::string Value() const { return m_Value; }

private:
    LexerTokenType m_Type;
    std::string m_Value;
};
