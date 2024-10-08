#pragma once
#include <string>

namespace Parser::AST {
    enum class NodeKind
    {
        CONST,
        VARIABLE,
        MULT, 
        REMAINDER,
        DIV, 
        ADD,
        SUBTRACT, 
        LSHIFT,
        RSHIFT,
        LESS,
        GREATER,
        LESSEQUAL,
        GREATEREQUAL,
        EQUAL,
        NOTEQUAL,
        BITAND,
        BITXOR,
        BITOR,
        LOGICALAND,
        LOGICALOR,
        ASSIGN,
        PLUSASSIGN,
        MINUSASSIGN,
        MULTASSIGN,
        DIVASSIGN,
        REMASSIGN,
        ANDASSIGN,
        XORASSIGN,
        ORASSIGN,
        LSHIFTASSIGN,
        RSHIFTASSIGN,
        UNARYMINUS,
    };

    std::string ToString(NodeKind kind);
}
