#pragma once
#include <vector>
#include <ostream>
#include "DiagnosticMessage.h"

namespace Diagnostic {
    class Diagnostic final
    {
    public:
        size_t Size() const noexcept { return m_Messages.size(); }
        DiagnosticMessage At(size_t pos) const { return m_Messages.at(pos); }

        void AddMessage(const DiagnosticMessage& message)
        {
            m_Messages.push_back(message);
        }

    private:
        std::vector<DiagnosticMessage> m_Messages;
        
    };

    std::ostream& operator<<(std::ostream& ostr, const Diagnostic& diagnostic);
}