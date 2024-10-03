#pragma once
#include <string>

namespace Lexer {
    enum class TokenType
    {
        NUM, ID, STRING, FUNC, VAR, VAL, RETURN, PRINT, IF, ELSE, WHILE, LBRA, RBRA, LPAR, RPAR, LIND, RIND,
        INCREMENT, DECREMENT, PLUS, MINUS, MULT, DIV, REMAINDER,
        LESS, LESSEQUAL, GREATER, GREATEREQUAL, EQUAL, NOTEQUAL,
        NOT, AND, OR,
        BITNOT, BITAND, BITOR, BITXOR, SHIFTLEFT, SHIFTRIGHT,
        ASSIGN, PLUSASSIGN, MINUSASSIGN, MULTASSIGN, DIVASSIGN, REMAINDERASSIGN,
        BITANDASSIGN, BITXORASSIGN, BITORASSIGN, LEFTSHIFTASSIGN, RIGHTSHIFTASSIGN,
        COLON, SEMICOLON, COMMA, DOT, ENDOFFILE
    };


    std::string ToString(TokenType type);

    class Token
    {
    public:
        Token(TokenType type, const std::string& value) : m_Type(type), m_Value(value) {}

        TokenType Type() const { return m_Type; }
        std::string Value() const { return m_Value; }

    private:
        TokenType m_Type;
        std::string m_Value;
    };
}