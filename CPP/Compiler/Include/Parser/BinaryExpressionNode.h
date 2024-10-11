#pragma once
#include <stdexcept>
#include <memory>
#include "Parser/ExpressionNode.h"

namespace Parser::AST {
    class BinaryExpressionNode : public ExpressionNode
    {
    public:
        BinaryExpressionNode(Op kind, std::unique_ptr<ExpressionNode> operandLeft, std::unique_ptr<ExpressionNode> operandRight) : ExpressionNode(kind)
        {
            if (!operandLeft) throw std::invalid_argument(__FUNCTION__ " : operandLeft was null.");
            if (!operandRight) throw std::invalid_argument(__FUNCTION__ " : operandRight was null.");

            m_OperandLeft = std::move(operandLeft);
            m_OperandRight = std::move(operandRight);
        }
        BinaryExpressionNode(const BinaryExpressionNode&) = delete;
        BinaryExpressionNode& operator=(const BinaryExpressionNode&) = delete;

        ExpressionNode* OpLeft() const { return m_OperandLeft.get(); }
        ExpressionNode* OpRight() const { return m_OperandRight.get(); }
    private:
        std::unique_ptr<ExpressionNode> m_OperandLeft;
        std::unique_ptr<ExpressionNode> m_OperandRight;
    };
}
