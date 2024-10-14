#include "Parser/Op.h"

namespace Parser::AST {
    std::string ToString(Op kind)
    {
        switch (kind)
        {
        case Op::CONST: return "CONST";
        case Op::ID: return "ID";
        case Op::MULT: return "MULT";
        case Op::REMAINDER: return "REMAINDER";
        case Op::DIV: return "DIV";
        case Op::ADD: return "ADD";
        case Op::SUBTRACT: return "SUBTRACT";
        case Op::LSHIFT: return "LSHIFT";
        case Op::RSHIFT: return "RSHIFT";
        case Op::LESS: return "LESS";
        case Op::GREATER: return "GREATER";
        case Op::LESSEQUAL: return "LESSEQUAL";
        case Op::GREATEREQUAL: return "GREATEREQUAL";
        case Op::EQUAL: return "EQUAL";
        case Op::NOTEQUAL: return "NOTEQUAL";
        case Op::BITAND: return "BITAND";
        case Op::BITXOR: return "BITXOR";
        case Op::BITOR: return "BITOR";
        case Op::LOGICALAND: return "LOGICALAND";
        case Op::LOGICALOR: return "LOGICALOR";
        case Op::ASSIGN: return "ASSIGN";
        case Op::PLUSASSIGN: return "PLUSASSIGN";
        case Op::MINUSASSIGN: return "MINUSASSIGN";
        case Op::MULTASSIGN: return "MULTASSIGN";
        case Op::DIVASSIGN: return "DIVASSIGN";
        case Op::REMASSIGN: return "REMASSIGN";
        case Op::ANDASSIGN: return "ANDASSIGN";
        case Op::XORASSIGN: return "XORASSIGN";
        case Op::ORASSIGN: return "ORASSIGN";
        case Op::LSHIFTASSIGN: return "LSHIFTASSIGN";
        case Op::RSHIFTASSIGN: return "RSHIFTASSIGN";
        case Op::UNARYMINUS: return "UNARYMINUS";
        case Op::NOT: return "NOT";
        case Op::BITNOT: return "BITNOT";
        case Op::PREINC: return "PREINC";
        case Op::PREDEC: return "PREDEC";
        case Op::POSTINC: return "POSTINC";
        case Op::POSTDEC: return "POSTDEC";
        case Op::MEMBER: return "MEMBER";
        case Op::INDEX: return "INDEX";
        case Op::CALL: return "CALL";
        case Op::SEQUENCE: return "SEQUENCE";
        default: return "UNKNOWN";
        }
    }
}