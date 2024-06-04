#include "controller.h"

void Controller::run() {
    view.accountInteraction(account);
    while (true) {
        account.getData(account.getName());
        view.menuInteraction(account);
        startGame();
    }
}

void Controller::startGame() {
    while (true) {
        cout << "\nВиберіть режим (classic/hidden/proverb/sentence/hangman)" << endl;
        cout << "Classic - класичний варіант гри в \"Слова\"" << endl;
        cout << "Hidden - режим, де частина букв замінені на '*'. Цей режим підходить тим, хто вже трохи пограв у класичний режим" << endl;
        cout << "Sentence - режим для тих, кому гра з одним словом здається нудною. Відгадуйте одразу декілька слів." << endl;
        cout << "Hangman - стара класична гра, де ви вгадуєте які літери є в слові і вгадуєте саме слово, доки спроби не закінчаться." << endl;
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

    system("clear");

    cout << "Вибраний режим: " << mode << endl;
    cout << "Вибрана складність: " << difficulty << endl;

    if (mode == Classic) {
        WordsClassic wordsClassic(account, difficulty, "input.txt");
        wordsClassic.runWordsClassic();
    } else if (mode == Sentence) {
        WordsSentence wordsSentence(account, difficulty, "input.txt");
        wordsSentence.runWordsSentence();
    } else if (mode == Hidden) {
        WordsHidden wordsHidden(account, difficulty, "input.txt");
        wordsHidden.runWordsHidden();
    }
    else if (mode == Hangman) {
        WordsHangman wordsHangman(account, difficulty, "input.txt");
        wordsHangman.runWordsHangman();
    }
    endGame();
}

void Controller::endGame() {
    system("clear");
    account.getData(account.getName());
    if (account.getName() != "") {
        addToLeaderboard("gamesLeaderboard.txt");
        addToLeaderboard("winsLeaderboard.txt");
        addToLeaderboard("winsInARowLeaderboard.txt");
    }
}

void Controller::addToLeaderboard(string filename) {
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
}