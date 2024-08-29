#include "Lexer.h"
#include <iostream>
#include <unordered_map>

Lexer::Lexer(const std::string& filePath) : m_InputStream(filePath),
    m_CurrentChar(' '), m_StringNumber(1), m_CharNumber(1) { }

LexerToken Lexer::NextToken()
{
    static const std::unordered_map<char, LexerTokenType> symbolsMap({
        {'{', LexerTokenType::LBRA}, {'}', LexerTokenType::RBRA}, {'=', LexerTokenType::EQUAL}, 
        {';', LexerTokenType::SEMICOLON}, {'(', LexerTokenType::LPAR}, {')', LexerTokenType::RPAR},
        {'+', LexerTokenType::PLUS}, {'-', LexerTokenType::MINUS}, {'*', LexerTokenType::MULT},
        {'/', LexerTokenType::DIV}, {'<', LexerTokenType::LESS}
        });

    static const std::unordered_map<std::string, LexerTokenType> keywordsMap({
        {"print", LexerTokenType::PRINT}, {"if", LexerTokenType::IF},
        {"else", LexerTokenType::ELSE}, {"while", LexerTokenType::WHILE}
        });

    std::string val;
    LexerTokenType type;
    bool found = false;

    while (!found)
    {
        if (m_InputStream.eof())
        {
            type = LexerTokenType::ENDOFFILE;
            found = true;
        }
        else if (isspace(m_CurrentChar))
        {
            NextChar();
        }
        else if (m_CurrentChar == '\'')
        {
            type = LexerTokenType::STRING;
            val = ParseString();
            found = true;

            NextChar();
        }
        else if (isdigit(m_CurrentChar))
        {
            type = LexerTokenType::NUM;
            val = ParseNumber();
            found = true;
        }
        else if (auto iter = symbolsMap.find(m_CurrentChar); iter != symbolsMap.end())
        {
            type = iter->second;
            found = true;

            NextChar();
        }
        else if (isalpha(m_CurrentChar) || m_CurrentChar == '_')
        {
            std::string ident = ParseIdentifier();
            auto iter = keywordsMap.find(ident);
            if (iter != keywordsMap.end())
            {
                type = iter->second;
            }
            else
            {
                type = LexerTokenType::ID;
                val = std::move(ident);
            }
            found = true;
        }
        else
        {
            std::string error = "Unexpected symbol:  ";
            error.back() = m_CurrentChar;
            ThrowError(error);
        }
    }

    return LexerToken(type, std::move(val));
}

void Lexer::ThrowError(const std::string& error) const
{
    std::cout << '(' << m_StringNumber << ':' << m_CharNumber << ") " << error << std::endl;
    exit(-1);
}

void Lexer::NextChar()
{
    if (!m_InputStream.eof())
    {
        m_InputStream >> m_CurrentChar;
    }
    else
    {
        m_CurrentChar = EOF;
    }

    ++m_CharNumber;
    if (m_CurrentChar == '\n')
    {
        ++m_StringNumber;
        m_CharNumber = 1;
    }
}

void Lexer::ParseSpecialSymbol()
{
    static const std::unordered_map<char, char> specialSymbolTable({
        {'a', '\a'},
        {'b', '\b'},
        {'f', '\f'},
        {'n', '\n'},
        {'r', '\r'},
        {'t', '\t'},
        {'v', '\v'},
        });

    auto iter = specialSymbolTable.find(m_CurrentChar);
    if (iter != specialSymbolTable.end())
    {
        m_CurrentChar = iter->second;
    }
}

std::string Lexer::ParseString()
{
    std::string parsedString;
    NextChar();

    while (m_CurrentChar != '\'')
    {
        if (m_CurrentChar == EOF)
        {
            ThrowError("Unexpected EOF");
        }

        if (m_CurrentChar == '\\')
        {
            NextChar();
            ParseSpecialSymbol();
        }

        parsedString.push_back(m_CurrentChar);
        NextChar();
    }

    return parsedString;
}

std::string Lexer::ParseNumber()
{
    std::string val;
    while (isdigit(m_CurrentChar))
    {
        val.push_back(m_CurrentChar);
        NextChar();
    }

    return val;
}

std::string Lexer::ParseIdentifier()
{
    std::string ident;

    while (isalnum(m_CurrentChar) || m_CurrentChar == '_')
    {
        ident.push_back(m_CurrentChar);
        NextChar();
    }

    return ident;
}
