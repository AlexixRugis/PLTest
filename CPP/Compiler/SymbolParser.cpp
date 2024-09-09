#include "SymbolParser.h"
#include "TokenSearchTrie.h"
#include <unordered_map>
#include <string>

namespace Lexer {
    static const TokenSearchTrie symbolsMap{
        std::make_pair<std::string, TokenType>("{", TokenType::LBRA),
        std::make_pair<std::string, TokenType>("}", TokenType::RBRA),
        std::make_pair<std::string, TokenType>("(", TokenType::LPAR),
        std::make_pair<std::string, TokenType>(")", TokenType::RPAR),
        std::make_pair<std::string, TokenType>("[", TokenType::LIND),
        std::make_pair<std::string, TokenType>("]", TokenType::RIND),
        std::make_pair<std::string, TokenType>("++", TokenType::INCREMENT),
        std::make_pair<std::string, TokenType>("--", TokenType::DECREMENT),
        std::make_pair<std::string, TokenType>("+", TokenType::PLUS),
        std::make_pair<std::string, TokenType>("-", TokenType::MINUS),
        std::make_pair<std::string, TokenType>("*", TokenType::MULT),
        std::make_pair<std::string, TokenType>("/", TokenType::DIV),
        std::make_pair<std::string, TokenType>("%", TokenType::REMAINDER),
        std::make_pair<std::string, TokenType>("<", TokenType::LESS),
        std::make_pair<std::string, TokenType>("<=", TokenType::LESSEQUAL),
        std::make_pair<std::string, TokenType>(">", TokenType::GREATER),
        std::make_pair<std::string, TokenType>(">=", TokenType::GREATEREQUAL),
        std::make_pair<std::string, TokenType>("==", TokenType::EQUAL),
        std::make_pair<std::string, TokenType>("!=", TokenType::NOTEQUAL),
        std::make_pair<std::string, TokenType>("!", TokenType::NOT),
        std::make_pair<std::string, TokenType>("&&", TokenType::AND),
        std::make_pair<std::string, TokenType>("||", TokenType::OR),
        std::make_pair<std::string, TokenType>("~", TokenType::BITNOT),
        std::make_pair<std::string, TokenType>("&", TokenType::BITAND),
        std::make_pair<std::string, TokenType>("|", TokenType::BITOR),
        std::make_pair<std::string, TokenType>("^", TokenType::BITXOR),
        std::make_pair<std::string, TokenType>("<<", TokenType::SHIFTLEFT),
        std::make_pair<std::string, TokenType>(">>", TokenType::SHIFTRIGHT),
        std::make_pair<std::string, TokenType>("=", TokenType::ASSIGN),
        std::make_pair<std::string, TokenType>("+=", TokenType::PLUSASSIGN),
        std::make_pair<std::string, TokenType>("-=", TokenType::MINUSASSIGN),
        std::make_pair<std::string, TokenType>("*=", TokenType::MULTASSIGN),
        std::make_pair<std::string, TokenType>("/=", TokenType::DIVASSIGN),
        std::make_pair<std::string, TokenType>("%=", TokenType::REMAINDERASSIGN),
        std::make_pair<std::string, TokenType>("&=", TokenType::BITANDASSIGN),
        std::make_pair<std::string, TokenType>("|=", TokenType::BITORASSIGN),
        std::make_pair<std::string, TokenType>("^=", TokenType::BITXORASSIGN),
        std::make_pair<std::string, TokenType>("<<=", TokenType::LEFTSHIFTASSIGN),
        std::make_pair<std::string, TokenType>(">>=", TokenType::RIGHTSHIFTASSIGN),
        std::make_pair<std::string, TokenType>(":", TokenType::COLON),
        std::make_pair<std::string, TokenType>(";", TokenType::SEMICOLON),
        std::make_pair<std::string, TokenType>(",", TokenType::COMMA),
        std::make_pair<std::string, TokenType>(".", TokenType::DOT)
    };

    std::optional<Token> SymbolParser::TryParse(LexerContext& context)
    {
        TokenSearchTrie::Searcher searcher = symbolsMap.GetSearcher();

        while (searcher.TryFeed(context.CurrentChar()))
        {
            context.NextChar();
        }

        std::optional<TokenType> type = searcher.Value();

        if (!type.has_value())
        {
            return std::nullopt;
        }

        return Token(type.value(), "");
    }
}