#include "leaderboard.h"

void Leaderboard::printLeaderboard(string filename) {
    cout << "┌────────────────────────────┬──────────────────┬───────────────┬──────────────────┐" << endl;
    cout << "│            Ім'я            │   Ігор зіграно   │    Перемог    │  Перемог підряд  │" << endl;

    ifstream fin(filename);
    if (!fin) {
        cout << "Cannot open input file" << endl;
        exit(1);
    }

    string line;
    string name;
    while (fin >> name) {
        int games, wins, winsInARow;
        fin >> games >> wins >> winsInARow;
        cout << "├────────────────────────────┼──────────────────┼───────────────┼──────────────────┤" << endl;

        cout << "│ " << setw(27) << left << name
             << "│ " << setw(16) << games
             << " │ " << setw(13) << wins
             << " │ " << setw(16) << winsInARow << " │" << endl;
    }
    cout << "└────────────────────────────┴──────────────────┴───────────────┴──────────────────┘" << endl;
    fin.close();
}
