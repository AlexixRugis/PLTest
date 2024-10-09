#pragma once
#include "Parser/Op.h"

namespace Parser::AST {
    class Node
    {
    public:
        Node(Op kind) : m_Kind(kind) {}
        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;
        virtual ~Node() = 0 {}

        Op Kind() const { return m_Kind; }
    private:
        Op m_Kind;
    };
}
