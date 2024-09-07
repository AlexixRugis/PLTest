#include "NumberParser.h"
#include <string>

std::optional<LexerToken> NumberParser::TryParse(LexerContext& context)
{
    if (context.CurrentChar() != '-' && !isdigit(context.CurrentChar()))
    {
        return std::nullopt;
    }

    std::string parsedNumber;
    uint64_t addedDigits = 0;

    if (context.CurrentChar() == '-')
    {
        parsedNumber.push_back('-');
        context.NextChar();
    }
    
    while (isdigit(context.CurrentChar()))
    {
        parsedNumber.push_back(context.CurrentChar());
        context.NextChar();
        addedDigits++;
    }
    
    if (addedDigits == 0)
    {
        return std::nullopt;
    }

    return LexerToken(LexerTokenType::NUM, parsedNumber);
}
