#ifndef WORDSSENTENCE_H
#define WORDSSENTENCE_H

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

class WordsSentence : public WordsGame {

public:
    WordsSentence(Account &a, Difficulty d, string fn);
    void runWordsSentence();
    vector<string> splitUTF8String(const string &str);
    string shuffleUTF8Word(const string &str);
    vector<string> splitSentenceIntoWords(const string &sentence);
    string shuffleUTF8Sentence(const string &sentence);
    bool compareSentences(const string &sentence1, const string &sentence2);
};

#endif