#ifndef WORDSHIDDEN_H
#define WORDSHIDDEN_H

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

class WordsHidden : public WordsGame {
    int count = 2;
public:
    WordsHidden(Account &a, Difficulty d, string fn);
    void runWordsHidden();
    vector<string> splitUTF8String(const string &str);
    string shuffleUTF8Word(const string &str);
    void changeRandomChar(vector<string> &utf8Chars, vector<int> &changedIndices, mt19937 &g, int n);
};

#endif // WORDSHIDDEN_H
