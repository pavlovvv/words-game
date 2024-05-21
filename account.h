#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class account {
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

    int addGame() {
        return games++;
    }

    int getWinsInARow() {
        return winsInARow;
    }

    int addWinsInARow() {
        return winsInARow++;
    }

    bool getLastResult() {
        return lastResult;
    }

    void setLastResult(bool result) {
        lastResult = result;
    }

    bool isNameTaken(string n) {
        ifstream fin("accounts.txt");
        if (!fin) {
            cout << "Cannot open input file.\n";
            return false;
        }
        string line;
        while (getline(fin, line)) {
            // Розділити рядок на окремі значення
            istringstream iss(line);
            string token;
//            if (!(iss >> name >> games >> wins >> winsInARow >> credits >> boolalpha >> lastResult)) {
//                cerr << "Error parsing line: " << line << endl;
//                continue; // Пропустити поточний рядок і перейти до наступного
//            }

            cout<<games;
            if (n == name) {
                fin.close();
                return true;
            }
        }
        fin.close();
        return false;
    }
};
