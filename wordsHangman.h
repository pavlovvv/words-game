#ifndef WORDSHANGMAN_H
#define WORDSHANGMAN_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <algorithm>
#include "account.h"
#include "leaderboard.h"
#include "wordsGame.h"
#include "unordered_set"

using namespace std;

class WordsHangman : public WordsGame {
public:
    WordsHangman(Account &a, Difficulty d, string fn);
    void runWordsHangman();
    vector<string> splitUTF8String(const string &str);
};

#endif