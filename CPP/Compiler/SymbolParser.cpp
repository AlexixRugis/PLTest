#include "SymbolParser.h"
#include "LexerTokenSearchTrie.h"
#include <unordered_map>
#include <string>

static const LexerTokenSearchTrie symbolsMap{
    std::make_pair<std::string, LexerTokenType>("{", LexerTokenType::LBRA),
    std::make_pair<std::string, LexerTokenType>("}", LexerTokenType::RBRA),
    std::make_pair<std::string, LexerTokenType>("=", LexerTokenType::ASSIGN),
    std::make_pair<std::string, LexerTokenType>(";", LexerTokenType::SEMICOLON),
    std::make_pair<std::string, LexerTokenType>("(", LexerTokenType::LPAR),
    std::make_pair<std::string, LexerTokenType>(")", LexerTokenType::RPAR),
    std::make_pair<std::string, LexerTokenType>("+", LexerTokenType::PLUS),
    std::make_pair<std::string, LexerTokenType>("-", LexerTokenType::MINUS),
    std::make_pair<std::string, LexerTokenType>("*", LexerTokenType::MULT),
    std::make_pair<std::string, LexerTokenType>("/", LexerTokenType::DIV),
    std::make_pair<std::string, LexerTokenType>("<", LexerTokenType::LESS),
    std::make_pair<std::string, LexerTokenType>("<=", LexerTokenType::LESSEQUAL),
    std::make_pair<std::string, LexerTokenType>(">", LexerTokenType::GREATER),
    std::make_pair<std::string, LexerTokenType>(">=", LexerTokenType::GREATEREQUAL),
    std::make_pair<std::string, LexerTokenType>("==", LexerTokenType::EQUAL),
    std::make_pair<std::string, LexerTokenType>("!=", LexerTokenType::NOTEQUAL),
};

std::optional<LexerToken> SymbolParser::TryParse(LexerContext& context)
{
    LexerTokenSearchTrie::Searcher searcher = symbolsMap.GetSearcher();

    while (searcher.TryFeed(context.CurrentChar()))
    {
        context.NextChar();
    }

    std::optional<LexerTokenType> type = searcher.Value();

    if (!type.has_value())
    {
        return std::nullopt;
    }

    return LexerToken(type.value(), "");
}
