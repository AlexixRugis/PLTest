#include "Diagnostic/DiagnosticSeverity.h"

namespace Diagnostic {

    std::string ToString(DiagnosticSeverity severity)
    {
        switch (severity)
        {
        case Diagnostic::DiagnosticSeverity::ERROR:
            return "Error";
        case Diagnostic::DiagnosticSeverity::WARNING:
            return "Warning";
        case Diagnostic::DiagnosticSeverity::INFORMATION:
            return "Info";
        case Diagnostic::DiagnosticSeverity::HINT:
            return "Hint";
        default:
            return "Unknown";
        }
    }
}