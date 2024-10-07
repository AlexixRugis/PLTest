#pragma once
#include <stdexcept>
#include "Parser/ExpressionNode.h"

namespace Parser::AST {
    class UnaryExpressionNode : public ExpressionNode
    {
    public:
        UnaryExpressionNode(NodeKind kind, ExpressionNode* operand) : ExpressionNode(kind), m_Operand(operand)
        {
            if (operand == nullptr) throw std::invalid_argument(__FUNCTION__ " : operand was null.");
        }
        UnaryExpressionNode(const UnaryExpressionNode&) = delete;
        UnaryExpressionNode& operator=(const UnaryExpressionNode&) = delete;

        virtual ~UnaryExpressionNode()
        {
            delete m_Operand;
        }

        ExpressionNode* Op() const { return m_Operand; }
    private:
        ExpressionNode* m_Operand;
    };
}
