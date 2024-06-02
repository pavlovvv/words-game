#ifndef MODE_H
#define MODE_H

#include <iostream>
#include <string>

enum Mode {
    Classic,
    Hidden,
    Proverb,
    Sentence,
    Hangman
};

std::istream &operator>>(std::istream &is, Mode &mode);
std::ostream &operator<<(std::ostream &os, const Mode &mode);

#endif // MODE_H
