#include <iostream>
#include <string>
#include "view.h"
#include "difficulty_enum.h"
#include "mode_enum.h"
#include "wordsgame.h"
#include "wordsClassic.h"
#include "wordsSentence.h"
#include "wordsHidden.h"

using namespace std;

class Controller {
private:
    View view;
    Mode mode;
    Difficulty difficulty;
    Account account;
public:

    void run() {
        view.accountInteraction(account);
        while (true) {
            account.getData(account.getName());
            view.menuInteraction(account);
            startGame();
        }
    }

    void startGame() {
        while (true) {
            cout << "\nВиберіть режим (classic/hidden/proverb/sentence/hangman)" << endl;
            cout << "Classic - класичний варіант гри в \"Слова\"" << endl;
            cout
                    << "Hidden - режим, де частина букв замінені на '*'. Цей режим підходить тим, хто вже трохи пограв у класичний режим"
                    << endl;
            cout << "Proverb - режим для тих, хто вважає, що він добре знає прислів'я і приказки." << endl;
            cout
                    << "Sentence - режим для тих, кому гра з одним словом здається нудною. Відгадуйте одразу декілька слів."
                    << endl;
            cout
                    << "Hangman - стара класична гра, де ви вгадуєте які літери є в слові і вгадуєте саме слово, доки шибениця не буде домальована до кінця."
                    << endl;
            cin >> mode;

            if (!cin.fail()) {
                break;
            } else {
                cin.clear();
                cout << "Некоректний режим. Спробуйте ще раз." << endl;
            }
        }

        while (true) {
            cout << "\nВиберіть складність (easy/medium/hard)" << endl;
            cout << "Easy - це складність, де у вас є 15 спроб. Підходить початківцям." << endl;
            cout << "Medium - складність, де у вас є 10 спроб. Більше підходить для тих, хто вже трохи пограв." << endl;
            cout << "Hard - максимальна складність. У ній буде всього 5 спроб. На цій скланості важко буде грати навіть досвідченим гравцям." << endl;
            cin >> difficulty;

            if (!cin.fail()) {
                break;
            } else {
                cin.clear();
                cout << "Некоректна складність. Спробуйте ще раз." << endl;
            }
        }
        cout << "Вибраний режим: " << mode << endl;
        cout << "Вибрана складність: " << difficulty << endl;

        if (mode == Classic) {
            WordsClassic wordsClassic(account, mode, difficulty, "input.txt");
            wordsClassic.runWordsClassic();
            endGame();
        } else if (mode == Sentence) {
            WordsSentence wordsSentence(account, mode, difficulty, "input.txt");
            wordsSentence.runWordsSentence();
        } else if (mode == Hidden) {
            WordsHidden wordsHidden(account, mode, difficulty, "input.txt");
            wordsHidden.runWordsHidden();
        }
//        else if (mode == Proverb) {
//            WordsProverb wordsProverb(account, mode, difficulty, "input.txt");
//            wordsProverb.runWordsProverb();
//        }
        else if (mode == Hangman) {

        }
    }

    void endGame() {
        account.getData(account.getName());
        if (account.getName() != "") {
            addToLeaderboard("gamesLeaderboard.txt");
            addToLeaderboard("winsLeaderboard.txt");
            addToLeaderboard("winsInARowLeaderboard.txt");
        }
    }

    void addToLeaderboard(string filename) {
        ifstream fileIn(filename);
        if (!fileIn) {
            cout << "Cannot open input file" << endl;
            exit(1);
        }

        vector<string> leaderboard;
        string line;
        while (getline(fileIn, line)) {
            if (line.find(account.getName())) {
                leaderboard.push_back(line);
            }
        }
        fileIn.close();

        string newPlayer = account.getName() + " " + to_string(account.getGamesCount()) + " " +
                           to_string(account.getWins()) + " " + to_string(account.getWinsInARow());

        vector<string>::iterator it = leaderboard.end();
        for (auto iter = leaderboard.begin(); iter != leaderboard.end(); ++iter) {
            istringstream iss(*iter);
            string name;
            int games, wins, winsInARow;
            iss >> name >> games >> wins >> winsInARow;
            if (filename == "gamesLeaderboard.txt") {
                if (account.getGamesCount() >= games) {
                    it = iter;
                    break;
                }
            } else if (filename == "winsLeaderboard.txt") {
                if (account.getWins() >= wins) {
                    it = iter;
                    break;
                }
            } else if (filename == "winsInARowLeaderboard.txt") {
                if (account.getWinsInARow() >= winsInARow) {
                    it = iter;
                    break;
                }
            }
        }

        leaderboard.insert(it, newPlayer);

        if (leaderboard.size() > 10) {
            leaderboard.resize(10);
        }

        ofstream fileOut(filename);
        if (!fileOut) {
            cout << "Cannot open output file" << endl;
            exit(1);
        }
        int count = 0;
        for (auto it = leaderboard.begin(); it != leaderboard.end(); ++it) {
            if (!it->empty()) {
                if (count < 9) {
                    fileOut << *it << endl;
                } else {
                    fileOut << *it;
                }
                count++;
            }
        }
        fileOut.close();
    };
};