#include "IdentifierParser.h"
#include <unordered_map>
#include <string>

static const std::unordered_map<std::string, LexerTokenType> keywordsMap({
    {"print", LexerTokenType::PRINT}, {"if", LexerTokenType::IF},
    {"else", LexerTokenType::ELSE}, {"while", LexerTokenType::WHILE}
});

std::optional<LexerToken> IdentifierParser::TryParse(LexerContext& context)
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
        return LexerToken(iter->second, "");
    } else
    {
        return LexerToken(LexerTokenType::ID, ident);
    }
}
