#pragma once
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "ILexemParser.h"
#include "LexerToken.h"

class Lexer final
{
public:
    Lexer(const std::ifstream& ifs);

    LexerToken NextToken();

private:
    std::vector<std::shared_ptr<ILexemParser>> m_LexemParsers;

    std::string m_Text;
    uint64_t m_TextIndex;
    LexerContext m_Context;

    uint64_t m_LastStringNumber;
    uint64_t m_LastCharNumber;
    uint64_t m_LastTextIndex;

private:
    void ThrowError(const std::string& error) const;
    void NextChar();
    void AddParser(const std::shared_ptr<ILexemParser>&& parser);
    void Commit();
    void Rollback();

    std::string ReadFromFile(const std::ifstream& ifs);

    friend class LexerContext;
};