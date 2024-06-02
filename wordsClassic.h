#ifndef WORDSCLASSIC_H
#define WORDSCLASSIC_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <algorithm>
#include "account.h"
#include "leaderboard.h"
#include "api.h"
#include "wordsGame.h"

using namespace std;

class WordsClassic : public WordsGame {
    API api;
    int count = 2;
public:
    WordsClassic(Account &a, Difficulty d, string fn);
    void runWordsClassic();
    vector<string> splitUTF8String(const string &str);
    string shuffleUTF8Word(const string &str);
};

#endif