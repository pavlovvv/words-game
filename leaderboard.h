#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Leaderboard {
public:
    static void printLeaderboard(string filename) {
        cout << "┌────────────────────────────┬──────────────────┬───────────────┬──────────────────┐" << endl;
        cout << "│            Ім'я            │   Ігор зіграно   │    Перемог    │  Перемог підряд  │" << endl;
        ifstream fin(filename);
        if (!fin) {
            cout << "Cannot open input file" << endl;
            exit(1);
        }
        string line;
        while (getline(fin, line)) {
            cout << "├────────────────────────────┼──────────────────┼───────────────┼──────────────────┤" << endl;
            string name;
            int games, wins, winsInARow;

            fin >> name >> games >> wins >> winsInARow;
            cout << "│ " << setw(27) << left << name
                << "│ " << setw(16) << games
                << " │ " << setw(13) << wins
                << " │ " << setw(16) << winsInARow << " │" << endl;
        }
        cout << "└────────────────────────────┴──────────────────┴───────────────┴──────────────────┘" << endl;
        fin.close();
    }
};
