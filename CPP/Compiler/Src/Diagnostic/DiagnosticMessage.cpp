#include "Diagnostic/DiagnosticMessage.h"

namespace Diagnostic {
    std::ostream& operator<<(std::ostream& ostr, const DiagnosticMessage& message)
    {
        ostr << ToString(message.Severity()) << '\t' << ToString(message.Code()) << '\t' << message.Message() << "\t(" << message.Range() << ")";
        return ostr;
    }
}