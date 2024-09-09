#pragma once
#include <cstdint>

namespace Lexer {
    class Lexer;

    class LexerContext final
    {
    private:
        char m_CurrentChar;
        uint64_t m_StringNumber;
        uint64_t m_CharNumber;

        Lexer* m_Lexer;
    public:
        LexerContext(Lexer* lexer) : m_Lexer(lexer), m_CurrentChar(' '), m_StringNumber(1), m_CharNumber(1) {}
        LexerContext(const Lexer& lexer) = delete;

        char CurrentChar() const { return m_CurrentChar; }
        uint64_t StringNumber() const { return m_StringNumber; }
        uint64_t CharNumber() const { return m_CharNumber; }

        void NextChar();

        friend class Lexer;
    };
}