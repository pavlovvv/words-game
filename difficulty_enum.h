#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <iostream>
#include <string>

enum Difficulty {
    Easy,
    Medium,
    Hard
};

std::istream &operator>>(std::istream &is, Difficulty &difficulty);
std::ostream &operator<<(std::ostream &os, const Difficulty &difficulty);

#endif// DIFFICULTY_H