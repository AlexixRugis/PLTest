#include "IdentifierParser.h"
#include <unordered_map>
#include <string>

namespace Lexer {
    static const std::unordered_map<std::string, TokenType> keywordsMap({
        {"print", TokenType::PRINT}, {"if", TokenType::IF},
        {"else", TokenType::ELSE}, {"while", TokenType::WHILE}
        });

    std::optional<Token> IdentifierParser::TryParse(LexerContext& context)
    {
        if (context.CurrentChar() != '_' && !isalpha(context.CurrentChar()))
        {
            return std::nullopt;
        }

        std::string ident;

        while (context.CurrentChar() == '_' || isalnum(context.CurrentChar()))
        {
            ident.push_back(context.CurrentChar());
            context.NextChar();
        }

        auto iter = keywordsMap.find(ident);
        if (iter != keywordsMap.end())
        {
            return Token(iter->second, "");
        } else
        {
            return Token(TokenType::ID, ident);
        }
    }
}