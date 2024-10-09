#pragma once
#include <string>
#include "Parser/ExpressionNode.h"

namespace Parser::AST {
    class VariableNode final : public ExpressionNode
    {
    public:
        VariableNode(Op kind, std::string name) : ExpressionNode(kind), m_Name(name) {}
        VariableNode(const VariableNode&) = delete;
        VariableNode& operator=(const VariableNode&) = delete;

        std::string Name() const { return m_Name; }
    private:
        std::string m_Name;
    };
}
