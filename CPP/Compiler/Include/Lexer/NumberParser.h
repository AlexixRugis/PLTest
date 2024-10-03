#pragma once
#include <optional>
#include "Lexer/LexerContext.h"
#include "Lexer/ILexemParser.h"

namespace Lexer {
    class NumberParser final : public ILexemParser
    {
    public:
        std::optional<Token> TryParse(LexerContext& context);
    };
}