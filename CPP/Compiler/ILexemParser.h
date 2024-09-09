#pragma once
#include <optional>
#include "LexerContext.h"
#include "LexerToken.h"

namespace Lexer {
    class ILexemParser
    {
    public:
        virtual std::optional<Token> TryParse(LexerContext& context) = 0;
        virtual ~ILexemParser() {};
    };
}
