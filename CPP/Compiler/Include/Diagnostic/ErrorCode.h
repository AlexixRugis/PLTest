#pragma once
#include <string>

namespace Diagnostic {
    enum class ErrorCode
    {
        LEXER_ERROR = 1,
    };

    std::string ToString(ErrorCode code);
}
