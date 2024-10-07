#pragma once
#include <string>
#include <ostream>
#include "Text/FileRange.h"
#include "DiagnosticSeverity.h"
#include "ErrorCode.h"

namespace Diagnostic {
    class DiagnosticMessage final
    {
    public:
        DiagnosticMessage(DiagnosticSeverity severity, ErrorCode code, Text::FileRange range, const std::string& message) :
            m_Severity(severity), m_ErrorCode(code), m_Range(range), m_Message(message) {}

        DiagnosticSeverity Severity() const noexcept { return m_Severity; }
        ErrorCode Code() const noexcept { return m_ErrorCode; }
        Text::FileRange Range() const noexcept { return m_Range; }
        std::string Message() const noexcept { return m_Message; }

    private:
        DiagnosticSeverity m_Severity;
        ErrorCode m_ErrorCode;
        Text::FileRange m_Range;
        std::string m_Message;
    };

    std::ostream& operator<<(std::ostream& ostr, const DiagnosticMessage& message);
}
