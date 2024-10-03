#pragma once
#include "Parser/NodeKind.h"

namespace Parser::AST {
    class Node
    {
    public:
        Node(NodeKind kind) : m_Kind(kind) {}
        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;
        virtual ~Node() = 0 {}

        NodeKind Kind() const { return m_Kind; }
    private:
        NodeKind m_Kind;
    };
}
