#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <iomanip>
#include "account.h"
#include "leaderboard.h"

using namespace std;

class View {
private:
    Leaderboard leaderboard;
public:
    void accountInteraction(Account &account);
    void menuInteraction(Account &account);
    void printAccountData(Account &account);
    void printCurrentAttemptTable(string shuffledWord, int attempts, string hint, int credits);
    void printSpaces(int n);
    int countUTF8Characters(const string &str);
    int countIntCharacters(int a);
};

#endif // VIEW_H
