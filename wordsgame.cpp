#include "wordsgame.h"

WordsGame::WordsGame(Account &a, Difficulty d, string fn) : filename(fn), account(a), difficulty(d), count(1) {}

void WordsGame::addCount() {
    count++;
}

int WordsGame::getAttempts() {
    return attempts;
}

void WordsGame::setWord() {
    ifstream fin("input.txt");

    if (!fin.is_open()) {
        cerr << "Помилка: не вдалося відкрити файл зі словами." << endl;
        exit(1);
    }

    vector<string> words;
    string word;
    int c = 0;
    while (fin >> word) {
        words.push_back(word);
        if (c == count) {
            currentWord = word;
        }
        c++;
    }
    fin.close();
}

void WordsGame::runGame() {
    setWord();
    addCount();
    attempts = 15;
    switch (difficulty) {
        case Easy:
            break;
        case Medium:
            attempts = attempts / 1.5;
            break;
        case Hard:
            attempts = attempts / 3;
            break;
    }
}

void WordsGame::winGame() {
    cout << "Ви вгадали!!!!" << endl;
    if (difficulty == Easy) {
        account.endGame(true, account.getCredits() + 5);
    } else if (difficulty == Medium) {
        account.endGame(true, account.getCredits() + 15);
    } else {
        account.endGame(true, account.getCredits() + 25);
    }
}
