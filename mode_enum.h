enum Mode{
    Classic,
    Hidden,
    Proverb,
    Sentence,
    Hangman
};

inline istream& operator>>(istream& is, Mode& mode) {
    string modeStr;
    is >> modeStr;
    if (modeStr == "classic" || modeStr == "Classic") mode = Classic;
    else if (modeStr == "hidden" || modeStr == "Hidden") mode = Hidden;
    else if (modeStr == "proverb" || modeStr == "Proverb") mode = Proverb;
    else if (modeStr == "sentence" || modeStr == "Sentence") mode = Sentence;
    else if (modeStr == "hangman" || modeStr == "Hangman") mode = Hangman;
    else is.setstate(ios::failbit);
    return is;
}

inline ostream& operator<<(ostream& os, const Mode& mode) {
    switch (mode) {
        case Classic: os << "Classic"; break;
        case Hidden: os << "Hidden"; break;
        case Proverb: os << "Proverb"; break;
        case Sentence: os << "Sentence"; break;
        case Hangman: os << "Hangman"; break;
        default: os.setstate(ios::failbit);
    }
    return os;
}