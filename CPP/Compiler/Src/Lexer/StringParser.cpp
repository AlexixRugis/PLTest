#include "Lexer/StringParser.h"
#include <unordered_map>

namespace Lexer {
    std::optional<Token> StringParser::TryParse(LexerContext& context)
    {
        bool isInString = false;
        std::string parsedString;

        if (context.CurrentChar() != '\'')
        {
            return std::nullopt;
        }

        context.NextChar();
        while (context.CurrentChar() != '\'')
        {
            if (context.CurrentChar() == EOF)
            {
                // TODO: Add error info
                return std::nullopt;
            }

            char curChar = context.CurrentChar();

            if (curChar == '\\')
            {
                context.NextChar();
                curChar = TransformSpecialSymbol(context.CurrentChar());
            }

            parsedString.push_back(curChar);
            context.NextChar();
        }
        context.NextChar();

        return Token(TokenType::STRING, parsedString);
    }

    static const std::unordered_map<char, char> specialSymbolTable({
        {'a', '\a'},
        {'b', '\b'},
        {'f', '\f'},
        {'n', '\n'},
        {'r', '\r'},
        {'t', '\t'},
        {'v', '\v'},
        });

    char StringParser::TransformSpecialSymbol(char c) const
    {
        auto iter = specialSymbolTable.find(c);
        if (iter != specialSymbolTable.end())
        {
            return iter->second;
        }

        return c;
    }
}