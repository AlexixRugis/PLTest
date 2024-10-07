#include "Text/FilePos.h"

namespace Text {

    std::ostream& operator<<(std::ostream& ostr, const FilePos& filePos)
    {
        ostr << filePos.Line << ':' << filePos.Character;
        return ostr;
    }
}
