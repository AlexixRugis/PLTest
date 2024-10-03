#include <iostream>
#include <sstream>
#include <unordered_map>
#include "Lexer/Lexer.h"
#include "Lexer/StringParser.h"
#include "Lexer/NumberParser.h"
#include "Lexer/IdentifierParser.h"
#include "Lexer/SymbolParser.h"

namespace Lexer {
    Lexer::Lexer(const std::ifstream& ifs) : m_Context(this), m_Text(ReadFromFile(ifs)), m_TextIndex(0)
    {
        Commit();

        AddParser(std::make_shared<StringParser>());
        AddParser(std::make_shared<NumberParser>());
        AddParser(std::make_shared<SymbolParser>());
        AddParser(std::make_shared<IdentifierParser>());
    }

    Token Lexer::NextToken()
    {
        std::string val;
        TokenType type;
        bool found = false;

        while (!found)
        {
            if (m_TextIndex >= m_Text.size())
            {
                type = TokenType::ENDOFFILE;
                found = true;
                continue;
            } else if (isspace(m_Context.m_CurrentChar))
            {
                NextChar();
                Commit();
                continue;
            }

            for (auto& parser : m_LexemParsers)
            {
                std::optional<Token> token = parser.get()->TryParse(m_Context);
                if (token.has_value())
                {
                    type = token.value().Type();
                    val = token.value().Value();
                    found = true;
                    break;
                } else
                {
                    Rollback();
                }
            }

            if (!found)
            {
                std::string error = "Unexpected symbol:  ";
                error.back() = m_Context.m_CurrentChar;
                ThrowError(error);
            }
        }

        Commit();

        return Token(type, std::move(val));
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
        } else
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
}