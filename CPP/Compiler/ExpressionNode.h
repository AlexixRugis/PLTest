#pragma once
#include "Node.h"

namespace Parser::AST {
    class ExpressionNode : public Node {
    public:
        ExpressionNode(NodeKind kind) : Node(kind) { }
        ExpressionNode(const ExpressionNode&) = delete;
        ExpressionNode& operator=(const ExpressionNode&) = delete;
    };
}
