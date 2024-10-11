#pragma once
#include "Parser/Op.h"
#include <iostream>

namespace Parser::AST {
    class Node
    {
    public:
        Node(Op kind) : m_Kind(kind) { std::cout << "ctr\n"; }
        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;
        virtual ~Node() = 0 { std::cout << "destr\n"; }

        Op Kind() const { return m_Kind; }
    private:
        Op m_Kind;
    };
}