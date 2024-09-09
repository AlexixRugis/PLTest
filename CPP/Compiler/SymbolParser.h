#pragma once
#include <optional>
#include "LexerContext.h"
#include "ILexemParser.h"

namespace Lexer {
    class SymbolParser final : public ILexemParser
    {
    public:
        std::optional<Token> TryParse(LexerContext& context);
    };
}