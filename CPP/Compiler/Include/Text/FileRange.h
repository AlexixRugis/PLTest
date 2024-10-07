#pragma once
#include "FilePos.h"
#include <ostream>

namespace Text {
    struct FileRange final
    {
        FilePos Start;
        FilePos End;

        FileRange(FilePos start, FilePos end) : Start(start), End(end) {}
    };

    std::ostream& operator<<(std::ostream& ost, const FileRange& fileRange);
}
