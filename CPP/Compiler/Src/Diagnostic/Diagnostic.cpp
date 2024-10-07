#include "Diagnostic/Diagnostic.h"

namespace Diagnostic {
    std::ostream& operator<<(std::ostream& ostr, const Diagnostic& diagnostic)
    {
        for (size_t i = 0; i < diagnostic.Size(); ++i)
        {
            ostr << diagnostic.At(i) << '\n';
        }
        return ostr;
    }
}