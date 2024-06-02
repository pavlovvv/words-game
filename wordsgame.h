#ifndef WORDSGAME_H
#define WORDSGAME_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "account.h"
#include "view.h"
#include "difficulty_enum.h"

using namespace std;

class WordsGame {
protected:
    string filename;
    Account &account;
    Difficulty difficulty;
    int count;
    int attempts;
    View view;
    string currentWord;
    string shuffledWord;
public:
    WordsGame(Account &a, Difficulty d, string fn);

    void addCount();

    int getAttempts();

    void setWord();

    void runGame();

    void winGame();
};

#endif // WORDSGAME_H
