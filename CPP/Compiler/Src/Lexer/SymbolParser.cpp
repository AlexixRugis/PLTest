#include <unordered_map>
#include <string>
#include "Lexer/SymbolParser.h"
#include "Lexer/TokenSearchTrie.h"

namespace Lexer {
    static const TokenSearchTrie symbolsMap{
        {"{", TokenType::LBRA},
        {"}", TokenType::RBRA},
        {"(", TokenType::LPAR},
        {")", TokenType::RPAR},
        {"[", TokenType::LIND},
        {"]", TokenType::RIND},
        {"++", TokenType::INCREMENT},
        {"--", TokenType::DECREMENT},
        {"+", TokenType::PLUS},
        {"-", TokenType::MINUS},
        {"*", TokenType::MULT},
        {"/", TokenType::DIV},
        {"%", TokenType::REMAINDER},
        {"<", TokenType::LESS},
        {"<=", TokenType::LESSEQUAL},
        {">", TokenType::GREATER},
        {">=", TokenType::GREATEREQUAL},
        {"==", TokenType::EQUAL},
        {"!=", TokenType::NOTEQUAL},
        {"!", TokenType::NOT},
        {"&&", TokenType::AND},
        {"||", TokenType::OR},
        {"~", TokenType::BITNOT},
        {"&", TokenType::BITAND},
        {"|", TokenType::BITOR},
        {"^", TokenType::BITXOR},
        {"<<", TokenType::SHIFTLEFT},
        {">>", TokenType::SHIFTRIGHT},
        {"=", TokenType::ASSIGN},
        {"+=", TokenType::PLUSASSIGN},
        {"-=", TokenType::MINUSASSIGN},
        {"*=", TokenType::MULTASSIGN},
        {"/=", TokenType::DIVASSIGN},
        {"%=", TokenType::REMAINDERASSIGN},
        {"&=", TokenType::BITANDASSIGN},
        {"|=", TokenType::BITORASSIGN},
        {"^=", TokenType::BITXORASSIGN},
        {"<<=", TokenType::LEFTSHIFTASSIGN},
        {">>=", TokenType::RIGHTSHIFTASSIGN},
        {":", TokenType::COLON},
        {";", TokenType::SEMICOLON},
        {",", TokenType::COMMA},
        {".", TokenType::DOT}
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