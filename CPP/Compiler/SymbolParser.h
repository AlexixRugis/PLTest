#pragma once
#include <optional>
#include "LexerContext.h"
#include "ILexemParser.h"

class SymbolParser final : public ILexemParser
{
public:
    std::optional<LexerToken> TryParse(LexerContext& context);
};
