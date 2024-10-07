#include "Text/FileRange.h"

namespace Text {

    std::ostream& operator<<(std::ostream& ostr, const FileRange& fileRange)
    {
        ostr << fileRange.Start << " to " << fileRange.End;
        return ostr;
    }
}