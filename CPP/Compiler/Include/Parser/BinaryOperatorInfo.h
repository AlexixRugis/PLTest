#pragma once
#include <cstdint>

namespace Parser::AST {
    enum class BinaryOperatorAssociativity
    {
        LEFTTORIGHT,
        RIGHTTOLEFT
    };

    class BinaryOperatorInfo final
    {
    public:
        BinaryOperatorInfo(int32_t precedence, BinaryOperatorAssociativity associativity)
            : m_Precedence(precedence), m_Associativity(associativity) {}

        int32_t Precedence() const noexcept { return m_Precedence; }
        BinaryOperatorAssociativity Associativity() const noexcept { return m_Associativity; }

    private:
        int32_t m_Precedence;
        BinaryOperatorAssociativity m_Associativity;
    };
}
