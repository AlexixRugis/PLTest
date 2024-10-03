#pragma once
#include <stdexcept>
#include "Parser/ExpressionNode.h"

namespace Parser::AST {
    class BinaryExpressionNode : public ExpressionNode
    {
    public:
        BinaryExpressionNode(NodeKind kind, ExpressionNode* operandLeft, ExpressionNode* operandRight) 
            : ExpressionNode(kind), m_OperandLeft(operandLeft), m_OperandRight(operandRight)
        {
            if (operandLeft == nullptr) throw std::invalid_argument("BinaryExpressionNode::BinaryExpressionNode : operandLeft was null.");
            if (operandRight == nullptr) throw std::invalid_argument("BinaryExpressionNode::BinaryExpressionNode : operandRight was null.");
        }
        BinaryExpressionNode(const BinaryExpressionNode&) = delete;
        BinaryExpressionNode& operator=(const BinaryExpressionNode&) = delete;

        virtual ~BinaryExpressionNode()
        {
            delete m_OperandLeft;
            delete m_OperandRight;
        }

        ExpressionNode* OpLeft() const { return m_OperandLeft; }
        ExpressionNode* OpRight() const { return m_OperandRight; }
    private:
        ExpressionNode* m_OperandLeft;
        ExpressionNode* m_OperandRight;
    };
}
