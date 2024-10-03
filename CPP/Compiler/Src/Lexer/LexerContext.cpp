#include "Lexer/LexerContext.h"
#include "Lexer/Lexer.h"

namespace Lexer {
    void LexerContext::NextChar()
    {
        m_Lexer->NextChar();
    }
}