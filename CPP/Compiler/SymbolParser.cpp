#include "SymbolParser.h"
#include <unordered_map>

static const std::unordered_map<char, LexerTokenType> symbolsMap({
    {'{', LexerTokenType::LBRA}, {'}', LexerTokenType::RBRA}, {'=', LexerTokenType::EQUAL},
    {';', LexerTokenType::SEMICOLON}, {'(', LexerTokenType::LPAR}, {')', LexerTokenType::RPAR},
    {'+', LexerTokenType::PLUS}, {'-', LexerTokenType::MINUS}, {'*', LexerTokenType::MULT},
    {'/', LexerTokenType::DIV}, {'<', LexerTokenType::LESS}
    });

std::optional<LexerToken> SymbolParser::TryParse(LexerContext& context)
{
    auto iter = symbolsMap.find(context.CurrentChar());
    if (iter != symbolsMap.end())
    {
        context.NextChar();
        return LexerToken(iter->second, "");
    }

    return std::nullopt;
}
