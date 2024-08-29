#pragma once
#include <cstdint>
#include <fstream>
#include <string>
#include "LexerToken.h"

class Lexer
{
public:
    Lexer(const std::string& filePath);

    LexerToken NextToken();

private:
    std::ifstream m_InputStream;
    char m_CurrentChar;
    uint64_t m_StringNumber;
    uint64_t m_CharNumber;

private:
    void ThrowError(const std::string& error) const;
    void NextChar();
    void ParseSpecialSymbol();
    std::string ParseString();
    std::string ParseNumber();
    std::string ParseIdentifier();
};