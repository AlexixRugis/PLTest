#pragma once
#include "Parser/ExpressionNode.h"

namespace Parser::AST {
    class ConstNode final : public ExpressionNode
    {
    public:
        ConstNode(NodeKind kind, long long num) : ExpressionNode(kind), m_Value(num) {}
        ConstNode(const ConstNode&) = delete;
        ConstNode& operator=(const ConstNode&) = delete;

        long long Value() const { return m_Value; }
    private:
        long long m_Value;
    };
}
