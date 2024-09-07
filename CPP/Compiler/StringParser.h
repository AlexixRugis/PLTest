#pragma once
#include "ILexemParser.h"
#include "LexerContext.h"

class StringParser final : public ILexemParser
{
public:
    virtual std::optional<LexerToken> TryParse(LexerContext& context) override;
    virtual ~StringParser() {}

private:
    char TransformSpecialSymbol(char c) const;
};
