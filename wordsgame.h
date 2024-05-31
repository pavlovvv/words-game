#include <iostream>
#include <string>
#include <vector>

using namespace std;

class WordsGame {
protected:
    string filename;
    Account account;
    Mode mode;
    Difficulty difficulty;
    int count;
    View view;
    int attempts;
    string currentWord;
    string shuffledWord;
public:
    WordsGame(Account &a, Mode m, Difficulty d, string fn) : account(a), filename(fn), mode(m), difficulty(d), count(1) {}

    void addCount() {
        count++;
    }

    int getAttempts() {
        return attempts;
    }

    void setWord() {
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
            if (c==count) {
                currentWord = word;
            }
            c++;
        }
        fin.close();
    }

    void runGame() {
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
//        switch (mode) {
//            case Classic:
//                words.runClassic();
//                break;
//        }
    }
};
