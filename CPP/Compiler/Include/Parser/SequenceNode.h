#pragma once
#include <stdexcept>
#include <vector>
#include <memory>
#include "Parser/ExpressionNode.h"

namespace Parser::AST {
    class SequenceNode : public ExpressionNode
    {
    public:
        SequenceNode(Op kind) : ExpressionNode(kind) {}
        SequenceNode(const SequenceNode&) = delete;
        SequenceNode& operator=(const SequenceNode&) = delete;

        size_t size() const noexcept { return nodes.size(); }

        ExpressionNode* at(size_t index)
        {
            if (index >= nodes.size()) throw std::out_of_range(__FUNCTION__ " : index must be less than size");
            return nodes[index].get();
        }

        void appendNode(std::unique_ptr<ExpressionNode>&& node)
        {
            if (node.get() == nullptr) throw std::invalid_argument(__FUNCTION__ " : node was null");
            nodes.push_back(std::move(node));
        }

    private:
        std::vector<std::unique_ptr<ExpressionNode>> nodes;
    };
}
