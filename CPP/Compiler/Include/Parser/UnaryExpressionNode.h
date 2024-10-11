#pragma once
#include <stdexcept>
#include <memory>
#include "Parser/ExpressionNode.h"

namespace Parser::AST {
    class UnaryExpressionNode : public ExpressionNode
    {
    public:
        UnaryExpressionNode(Op kind, std::unique_ptr<ExpressionNode> operand) : ExpressionNode(kind)
        {
            if (!operand) throw std::invalid_argument(__FUNCTION__ " : operand was null.");

            m_Operand = std::move(operand);
        }
        UnaryExpressionNode(const UnaryExpressionNode&) = delete;
        UnaryExpressionNode& operator=(const UnaryExpressionNode&) = delete;

        ExpressionNode* Op() const { return m_Operand.get(); }
    private:
        std::unique_ptr<ExpressionNode> m_Operand;
    };
}
