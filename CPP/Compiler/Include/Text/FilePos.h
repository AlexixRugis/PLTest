#pragma once
#include <cstdint>
#include <ostream>

namespace Text {
    struct FilePos final
    {
        uint64_t Line;
        uint64_t Character;

        FilePos(uint64_t line, uint64_t character) : Line(line), Character(character) {}

        bool operator==(const FilePos& other) const { return Line == other.Line && Character == other.Character; }
        bool operator!=(const FilePos& other) const { return Line != other.Line || Character != other.Character; }
        bool operator<(const FilePos& other) const { return Line < other.Line || (Line == other.Line && Character < other.Character); }
        bool operator<=(const FilePos& other) const { return Line < other.Line || (Line == other.Line && Character <= other.Character); }
        bool operator>(const FilePos& other) const { return Line > other.Line || (Line == other.Line && Character > other.Character); }
        bool operator>=(const FilePos& other) const { return Line > other.Line || (Line == other.Line && Character >= other.Character); }
    };

    std::ostream& operator<<(std::ostream& ostr, const FilePos& filePos);
}

