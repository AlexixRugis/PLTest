#pragma once
#include <optional>
#include "Lexer/LexerContext.h"
#include "Lexer/LexerToken.h"

namespace Lexer {
    class ILexemParser
    {
    public:
        virtual std::optional<Token> TryParse(LexerContext& context) = 0;
        virtual ~ILexemParser() {};
    };
}
