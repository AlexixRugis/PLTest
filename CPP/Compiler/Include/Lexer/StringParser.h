#pragma once
#include "Lexer/ILexemParser.h"
#include "Lexer/LexerContext.h"

namespace Lexer {
    class StringParser final : public ILexemParser
    {
    public:
        virtual std::optional<Token> TryParse(LexerContext& context) override;
        virtual ~StringParser() {}

    private:
        char TransformSpecialSymbol(char c) const;
    };
}