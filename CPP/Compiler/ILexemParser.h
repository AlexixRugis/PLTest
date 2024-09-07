#pragma once
#include <optional>
#include "LexerContext.h"
#include "LexerToken.h"

class ILexemParser
{
public:
    virtual std::optional<LexerToken> TryParse(LexerContext& context) = 0;
    virtual ~ILexemParser() {};
};
