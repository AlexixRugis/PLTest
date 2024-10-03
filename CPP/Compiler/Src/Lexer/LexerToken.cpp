#include "Lexer/LexerToken.h"


std::string Lexer::ToString(Lexer::TokenType tokenType)
{
    switch (tokenType)
    {
    case TokenType::NUM: return "NUM";
    case TokenType::ID: return "ID";
    case TokenType::STRING: return "STRING";
    case TokenType::PRINT: return "PRINT";
    case TokenType::FUNC: return "FUNC";
    case TokenType::VAR: return "VAR";
    case TokenType::VAL: return "VAL";
    case TokenType::RETURN: return "RETURN";
    case TokenType::IF: return "IF";
    case TokenType::ELSE: return "ELSE";
    case TokenType::WHILE: return "WHILE";
    case TokenType::LBRA: return "LBRA";
    case TokenType::RBRA: return "RBRA";
    case TokenType::LPAR: return "LPAR";
    case TokenType::RPAR: return "RPAR";
    case TokenType::LIND: return "LIND";
    case TokenType::RIND: return "RIND";
    case TokenType::INCREMENT: return "INCREMENT";
    case TokenType::DECREMENT: return "DECREMENT";
    case TokenType::PLUS: return "PLUS";
    case TokenType::MINUS: return "MINUS";
    case TokenType::MULT: return "MULT";
    case TokenType::DIV: return "DIV";
    case TokenType::REMAINDER: return "REMAINDER";
    case TokenType::LESS: return "LESS";
    case TokenType::LESSEQUAL: return "LESSEQUAL";
    case TokenType::GREATER: return "GREATER";
    case TokenType::GREATEREQUAL: return "GREATEREQUAL";
    case TokenType::EQUAL: return "EQUAL";
    case TokenType::NOTEQUAL: return "NOTEQUAL";
    case TokenType::NOT: return "NOT";
    case TokenType::AND: return "AND";
    case TokenType::OR: return "OR";
    case TokenType::BITNOT: return "BITNOT";
    case TokenType::BITAND: return "BITAND";
    case TokenType::BITOR: return "BITOR";
    case TokenType::BITXOR: return "BITXOR";
    case TokenType::SHIFTLEFT: return "SHIFTLEFT";
    case TokenType::SHIFTRIGHT: return "SHIFTRIGHT";
    case TokenType::ASSIGN: return "ASSIGN";
    case TokenType::PLUSASSIGN: return "PLUSASSIGN";
    case TokenType::MINUSASSIGN: return "MINUSASSIGN";
    case TokenType::MULTASSIGN: return "MULTASSIGN";
    case TokenType::DIVASSIGN: return "DIVASSIGN";
    case TokenType::REMAINDERASSIGN: return "REMAINDERASSIGN";
    case TokenType::BITANDASSIGN: return "BITANDASSIGN";
    case TokenType::BITXORASSIGN: return "BITXORASSIGN";
    case TokenType::BITORASSIGN: return "BITORASSIGN";
    case TokenType::LEFTSHIFTASSIGN: return "LEFTSHIFTASSIGN";
    case TokenType::RIGHTSHIFTASSIGN: return "RIGHTSHIFTASSIGN";
    case TokenType::COLON: return "COLON";
    case TokenType::SEMICOLON: return "SEMICOLON";
    case TokenType::COMMA: return "COMMA";
    case TokenType::DOT: return "DOT";
    case TokenType::ENDOFFILE: return "ENDOFFILE";
    }
    return "UNKNOWN"; // Fallback for any unhandled cases
}