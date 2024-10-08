#include "Parser/NodeKind.h"

namespace Parser::AST {
    std::string ToString(NodeKind kind)
    {
        switch (kind)
        {
        case NodeKind::CONST: return "CONST";
        case NodeKind::VARIABLE: return "VARIABLE";
        case NodeKind::MULT: return "MULT";
        case NodeKind::REMAINDER: return "REMAINDER";
        case NodeKind::DIV: return "DIV";
        case NodeKind::ADD: return "ADD";
        case NodeKind::SUBTRACT: return "SUBTRACT";
        case NodeKind::LSHIFT: return "LSHIFT";
        case NodeKind::RSHIFT: return "RSHIFT";
        case NodeKind::LESS: return "LESS";
        case NodeKind::GREATER: return "GREATER";
        case NodeKind::LESSEQUAL: return "LESSEQUAL";
        case NodeKind::GREATEREQUAL: return "GREATEREQUAL";
        case NodeKind::EQUAL: return "EQUAL";
        case NodeKind::NOTEQUAL: return "NOTEQUAL";
        case NodeKind::BITAND: return "BITAND";
        case NodeKind::BITXOR: return "BITXOR";
        case NodeKind::BITOR: return "BITOR";
        case NodeKind::LOGICALAND: return "LOGICALAND";
        case NodeKind::LOGICALOR: return "LOGICALOR";
        case NodeKind::ASSIGN: return "ASSIGN";
        case NodeKind::PLUSASSIGN: return "PLUSASSIGN";
        case NodeKind::MINUSASSIGN: return "MINUSASSIGN";
        case NodeKind::MULTASSIGN: return "MULTASSIGN";
        case NodeKind::DIVASSIGN: return "DIVASSIGN";
        case NodeKind::REMASSIGN: return "REMASSIGN";
        case NodeKind::ANDASSIGN: return "ANDASSIGN";
        case NodeKind::XORASSIGN: return "XORASSIGN";
        case NodeKind::ORASSIGN: return "ORASSIGN";
        case NodeKind::LSHIFTASSIGN: return "LSHIFTASSIGN";
        case NodeKind::RSHIFTASSIGN: return "RSHIFTASSIGN";
        case NodeKind::UNARYMINUS: return "UNARYMINUS";
        default: return "UNKNOWN";
        }
    }
}