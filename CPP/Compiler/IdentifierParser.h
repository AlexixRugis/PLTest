#pragma once
#include <optional>
#include "LexerContext.h"
#include "ILexemParser.h"

namespace Lexer {
    class IdentifierParser final : public ILexemParser
    {
    public:
        std::optional<Token> TryParse(LexerContext& context);
    };
}
