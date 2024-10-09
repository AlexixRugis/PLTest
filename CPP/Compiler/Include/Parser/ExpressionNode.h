#pragma once
#include "Parser/Node.h"

namespace Parser::AST {
    class ExpressionNode : public Node
    {
    public:
        ExpressionNode(Op kind) : Node(kind) {}
        ExpressionNode(const ExpressionNode&) = delete;
        ExpressionNode& operator=(const ExpressionNode&) = delete;
    };
}
