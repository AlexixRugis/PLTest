#pragma once
#include <string>

namespace Diagnostic {
    enum class DiagnosticSeverity
    {
        ERROR = 1,
        WARNING,
        INFORMATION,
        HINT
    };

    std::string ToString(DiagnosticSeverity severity);
}
