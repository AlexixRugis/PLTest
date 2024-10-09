#pragma once
#include <string>

namespace Parser::AST {
    enum class Op
    {
        CONST,
        ID,
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
        NOT,
        BITNOT,
        PREINC,
        PREDEC,
        POSTINC,
        POSTDEC,
        INDEX,
        MEMBER,
        CALL
    };

    std::string ToString(Op kind);
}
