#include "account.h"

string Account::getName() {
    return name;
}

void Account::setName(string n) {
    name = n;
}

int Account::getGamesCount() {
    return games;
}

void Account::setGamesCount(int g) {
    games = g;
}

void Account::addGame() {
    games++;
}

int Account::getWinsInARow() {
    return winsInARow;
}

void Account::setWins(int w) {
    wins = w;
}

int Account::getWins() {
    return wins;
}

void Account::setWinsInARow(int wiar) {
    winsInARow = wiar;
}

int Account::getCredits() {
    return credits;
}

void Account::setCredits(int c) {
    credits = c;
}

bool Account::getLastResult() {
    return lastResult;
}

void Account::setLastResult(bool result) {
    lastResult = result;
}

bool Account::endGame(bool result, int c) {
    fstream file("accounts.txt");
    if (!file) {
        cout << "Cannot open input file" << endl;
        return false;
    }
    string nameFromFile;
    while (file >> nameFromFile) {
        if (name == nameFromFile) {
            file << " " << games + 1 << " " << (result ? wins + 1 : wins) << " " << (result ? winsInARow + 1 : 0)
                 << " " << c << " " << (result ? "true" : "false") << endl;
            setGamesCount(games + 1);
            setWins(result ? wins + 1 : wins);
            setWinsInARow(result ? winsInARow + 1 : 0);
            setCredits(c);
            setLastResult(result);
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void Account::createAccount(string n) {
    ofstream fout("accounts.txt", ios::app);
    fout << n << " 0 0 0 100 false" << endl;
    setName(n);
    setGamesCount(0);
    setWinsInARow(0);
    setWins(0);
    setCredits(100);
    setLastResult(false);
    fout.close();
}

bool Account::getData(string n) {
    ifstream fin("accounts.txt");
    if (!fin) {
        cout << "Cannot open input file" << endl;
        return false;
    }
    string nameFromFile;
    while (fin >> nameFromFile) {
        if (n == nameFromFile) {
            fin >> games >> wins >> winsInARow >> credits >> lastResult;
            setName(n);
            setGamesCount(games);
            setWins(wins);
            setWinsInARow(winsInARow);
            setCredits(credits);
            setLastResult(lastResult);
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}

void Account::enterAsGuest() {
    setGamesCount(0);
    setWinsInARow(0);
    setWins(0);
    setCredits(100);
    setLastResult(false);
}

