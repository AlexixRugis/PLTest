#pragma once
#include <string>

namespace Parser::AST {
    enum class NodeKind
    {
        CONST, ADD, SUBTRACT, MULT, DIV, UNARYMINUS,
    };

    std::string ToString(NodeKind kind);
}
