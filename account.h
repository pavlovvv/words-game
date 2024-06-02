#ifndef CURSOVA_ACCOUNT_H
#define CURSOVA_ACCOUNT_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Account {
private:
    string name;
    int games;
    int wins;
    int winsInARow;
    int credits;
    bool lastResult;

public:
    string getName();
    void setName(string n);
    int getGamesCount();
    void setGamesCount(int g);
    void addGame();
    int getWinsInARow();
    void setWins(int w);
    int getWins();
    void setWinsInARow(int wiar);
    int getCredits();
    void setCredits(int c);
    bool getLastResult();
    void setLastResult(bool result);
    bool endGame(bool result, int c);
    void createAccount(string n);
    bool getData(string n);
    void enterAsGuest();
};

#endif // CURSOVA_ACCOUNT_H