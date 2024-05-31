enum Difficulty{
    Easy,
    Medium,
    Hard
};

inline istream& operator>>(istream& is, Difficulty& difficulty) {
    string difficultyStr;
    is >> difficultyStr;
    if (difficultyStr == "easy" ||  difficultyStr == "Easy" || difficultyStr == "EASY") difficulty = Easy;
    else if (difficultyStr == "medium" || difficultyStr == "Medium" || difficultyStr == "MEDIUM") difficulty = Medium;
    else if (difficultyStr == "hard" || difficultyStr == "Hard" || difficultyStr == "HARD") difficulty = Hard;
    else is.setstate(ios::failbit);
    return is;
}

inline ostream& operator<<(ostream& os, const Difficulty& difficulty) {
    switch (difficulty) {
        case Easy: os << "Easy"; break;
        case Medium: os << "Medium"; break;
        case Hard: os << "Hard"; break;
        default: os.setstate(ios::failbit);
    }
    return os;
}