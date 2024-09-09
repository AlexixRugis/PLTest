#include "LexerContext.h"
#include "Lexer.h"

namespace Lexer {
    void LexerContext::NextChar()
    {
        m_Lexer->NextChar();
    }
}