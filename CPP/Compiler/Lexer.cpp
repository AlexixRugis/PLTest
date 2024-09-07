#include <iostream>
#include <sstream>
#include <unordered_map>
#include "Lexer.h"
#include "StringParser.h"

Lexer::Lexer(const std::ifstream& ifs) : m_Context(this), m_Text(ReadFromFile(ifs)), m_TextIndex(0)
{
    Commit();

    AddParser(std::make_shared<StringParser>());
}

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
        if (m_TextIndex >= m_Text.size())
        {
            type = LexerTokenType::ENDOFFILE;
            found = true;
            continue;
        }
        else if (isspace(m_Context.m_CurrentChar))
        {
            NextChar();
            Commit();
            continue;
        }

        for (auto& parser : m_LexemParsers)
        {
            std::optional<LexerToken> token = parser.get()->TryParse(m_Context);
            if (token.has_value())
            {
                type = token.value().Type();
                val = token.value().Value();
                found = true;
                break;
            }
            else
            {
                Rollback();
            }
        }

        if (found) continue;


        if (isdigit(m_Context.m_CurrentChar))
        {
            type = LexerTokenType::NUM;
            val = ParseNumber();
            found = true;
        }
        else if (auto iter = symbolsMap.find(m_Context.m_CurrentChar); iter != symbolsMap.end())
        {
            type = iter->second;
            found = true;

            NextChar();
        }
        else if (isalpha(m_Context.m_CurrentChar) || m_Context.m_CurrentChar == '_')
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
            error.back() = m_Context.m_CurrentChar;
            ThrowError(error);
        }
    }

    Commit();

    return LexerToken(type, std::move(val));
}

void Lexer::ThrowError(const std::string& error) const
{
    std::cout << '(' << m_Context.m_StringNumber << ':' << m_Context.m_CharNumber << ") " << error << std::endl;
    exit(-1);
}

void Lexer::NextChar()
{
    if (m_TextIndex < m_Text.size() - 1)
    {
        m_Context.m_CurrentChar = m_Text[++m_TextIndex];
    }
    else
    {
        m_TextIndex = m_Text.size();
        m_Context.m_CurrentChar = EOF;
    }

    ++m_Context.m_CharNumber;
    if (m_Context.m_CurrentChar == '\n')
    {
        ++m_Context.m_StringNumber;
        m_Context.m_CharNumber = 1;
    }
}

void Lexer::AddParser(const std::shared_ptr<ILexemParser>&& parser)
{
    m_LexemParsers.push_back(parser);
}

std::string Lexer::ParseNumber()
{
    std::string val;
    while (isdigit(m_Context.m_CurrentChar))
    {
        val.push_back(m_Context.m_CurrentChar);
        NextChar();
    }

    return val;
}

std::string Lexer::ParseIdentifier()
{
    std::string ident;

    while (isalnum(m_Context.m_CurrentChar) || m_Context.m_CurrentChar == '_')
    {
        ident.push_back(m_Context.m_CurrentChar);
        NextChar();
    }

    return ident;
}

std::string Lexer::ReadFromFile(const std::ifstream& ifs)
{
    std::ostringstream sstr;
    sstr << ifs.rdbuf();
    return sstr.str();
}

void Lexer::Commit()
{
    m_LastCharNumber = m_Context.CharNumber();
    m_LastStringNumber = m_Context.StringNumber();
    m_LastTextIndex = m_TextIndex;
    m_Context.m_CurrentChar = m_Text[m_TextIndex];
}

void Lexer::Rollback()
{
    m_Context.m_CharNumber = m_LastCharNumber;
    m_Context.m_StringNumber = m_LastStringNumber;
    m_TextIndex = m_LastTextIndex;
    m_Context.m_CurrentChar = m_Text[m_TextIndex];
}
