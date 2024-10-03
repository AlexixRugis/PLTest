#include "Parser/NodeKind.h"

namespace Parser::AST {
    std::string ToString(NodeKind kind)
    {
        switch (kind)
        {
        case Parser::AST::NodeKind::CONST:
            return "Parser::AST::NodeKind::CONST";
        case Parser::AST::NodeKind::ADD:
            return "Parser::AST::NodeKind::ADD";
        case Parser::AST::NodeKind::SUBTRACT:
            return "Parser::AST::NodeKind::SUBTRACT";
        case Parser::AST::NodeKind::MULT:
            return "Parser::AST::NodeKind::MULT";
        case Parser::AST::NodeKind::DIV:
            return "Parser::AST::NodeKind::DIV";
        case Parser::AST::NodeKind::UNARYMINUS:
            return "Parser::AST::NodeKind::UNARYMINUS";
        default:
            return "UNKNOWN";
        }
    }
}