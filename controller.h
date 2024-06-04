#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include "view.h"
#include "difficulty_enum.h"
#include "mode_enum.h"
#include "wordsgame.h"
#include "wordsClassic.h"
#include "wordsSentence.h"
#include "wordsHidden.h"
#include "wordsHangman.h"

using namespace std;

class Controller {
private:
    View view;
    Mode mode;
    Difficulty difficulty;
    Account account;
public:

    void run();
    void startGame();
    void endGame();
    void addToLeaderboard(string filename);
};

#endif