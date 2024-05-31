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
    string getName() {
        return name;
    }

    void setName(string n) {
        name = n;
    }

    int getGamesCount() {
        return games;
    }

    void setGamesCount(int g) {
        games = g;
    }

    void addGame() {
        games++;
    }

    int getWinsInARow() {
        return winsInARow;
    }

    void setWins (int w) {
        wins = w;
    }

    int getWins() {
        return wins;
    }

    void setWinsInARow (int wiar) {
        winsInARow = wiar;
    }

    int getCredits() {
        return credits;
    }

    void setCredits (int c) {
        credits = c;
    }

    bool getLastResult() {
        return lastResult;
    }

    void setLastResult(bool result) {
        lastResult = result;
    }

    bool endGame(bool result, int c) {
        fstream file("accounts.txt");
        if (!file) {
            cout << "Cannot open input file" << endl;
            return false;
        }
        string nameFromFile;
        while (file >> nameFromFile) {
            if (name == nameFromFile) {
                file << " " << games + 1 << " " << (result ? wins + 1 : wins) << " " << (result ? winsInARow + 1 : 0) << " " << c << " " << (result ? "true" : "false") << endl;
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

    void createAccount (string n) {
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

    bool getData(string n) {
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

    /*void createAccount (string n) {
        ofstream fout("accounts.txt", ios::app);
        fout << n << " 0 0 0 100 false" << endl;
        setName(n);
        setGamesCount(0);
        setWinsInARow(0);
        setWins(0);
        setCredits(100);
        setLastResult(false);
        fout.close();
    }*/

    void enterAsGuest () {
        setGamesCount(0);
        setWinsInARow(0);
        setWins(0);
        setCredits(100);
        setLastResult(false);
    }

//    string toLower(const string &str) {
//        string lowerStr = str;
//        for (char &c : lowerStr) {
//            c = tolower(static_cast<unsigned char>(c));
//        }
//        return lowerStr;
//    }
};
