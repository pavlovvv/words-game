#include "mode_enum.h"

std::istream &operator>>(std::istream &is, Mode &mode) {
    std::string modeStr;
    is >> modeStr;
    if (modeStr == "classic" || modeStr == "Classic") mode = Classic;
    else if (modeStr == "hidden" || modeStr == "Hidden") mode = Hidden;
    else if (modeStr == "sentence" || modeStr == "Sentence") mode = Sentence;
    else is.setstate(std::ios::failbit);
    return is;
}

std::ostream &operator<<(std::ostream &os, const Mode &mode) {
    switch (mode) {
        case Classic:
            os << "Classic";
            break;
        case Hidden:
            os << "Hidden";
            break;
        case Sentence:
            os << "Sentence";
            break;
        default:
            os.setstate(std::ios::failbit);
    }
    return os;
}
