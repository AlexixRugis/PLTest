#include "Diagnostic/ErrorCode.h"

namespace Diagnostic {
    std::string ToString(ErrorCode code)
    {
        switch (code)
        {
        case Diagnostic::ErrorCode::LEXER_ERROR:
            return "LEXER_ERROR";
        default:
            return "UNKNOWN";
        }
    }
}