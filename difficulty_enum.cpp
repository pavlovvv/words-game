#include "difficulty_enum.h"


std::istream &operator>>(std::istream &is, Difficulty &difficulty) {
    std::string difficultyStr;
    is >> difficultyStr;
    if (difficultyStr == "easy" || difficultyStr == "Easy" || difficultyStr == "EASY") difficulty = Easy;
    else if (difficultyStr == "medium" || difficultyStr == "Medium" || difficultyStr == "MEDIUM") difficulty = Medium;
    else if (difficultyStr == "hard" || difficultyStr == "Hard" || difficultyStr == "HARD") difficulty = Hard;
    else is.setstate(std::ios::failbit);
    return is;
}

std::ostream &operator<<(std::ostream &os, const Difficulty &difficulty) {
    switch (difficulty) {
        case Easy:
            os << "Easy";
            break;
        case Medium:
            os << "Medium";
            break;
        case Hard:
            os << "Hard";
            break;
        default:
            os.setstate(std::ios::failbit);
    }
    return os;
}