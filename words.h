#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <algorithm>
#include <chrono>

using namespace std;

class Words {
protected:
    string currentWord;
    string shuffledWord;
public:

    string getWord () {
        return currentWord;
    }

    string getShuffledWord () {
        return shuffledWord;
    }

    void setWord(int count) {
        ifstream fin("input.txt");

        if (!fin.is_open()) {
            cerr << "Помилка: не вдалося відкрити файл зі словами." << endl;
            exit(1);
        }

        vector<string> words;
        string word;
        while (fin >> word) {
            words.push_back(word);
        }

        fin.close();

        currentWord = words[count];
    }

    /*vector<string> splitUTF8String(const string &str) {
        vector<string> utf8Chars;
        for (size_t i = 0; i < str.size();) {
            size_t len = 1;
            if ((str[i] & 0x80) == 0x00) {
                len = 1; // 1-byte character (ASCII)
            } else if ((str[i] & 0xE0) == 0xC0) {
                len = 2; // 2-byte character
            } else if ((str[i] & 0xF0) == 0xE0) {
                len = 3; // 3-byte character
            } else if ((str[i] & 0xF8) == 0xF0) {
                len = 4; // 4-byte character
            }
            utf8Chars.push_back(str.substr(i, len));
            i += len;
        }
        return utf8Chars;
    }

    string shuffleUTF8Word(const string &str) {
        vector<string> utf8Chars = splitUTF8String(str);
        random_device rd;
        mt19937 g(rd());
        shuffle(utf8Chars.begin(), utf8Chars.end(), g);
        string shuffledStr;
        for (const auto &ch: utf8Chars) {
            shuffledStr += ch;
        }
        return shuffledStr;
    }

    vector<string> splitSentenceIntoWords(const string &sentence) {
        vector<string> words;
        istringstream stream(sentence);
        string word;
        while (stream >> word) {
            words.push_back(word);
        }
        return words;
    }

    string shuffleUTF8Sentence(const string &sentence) {
        vector<string> words = splitSentenceIntoWords(sentence);
        string shuffledSentence;
        for (auto &word: words) {
            if (!shuffledSentence.empty()) {
                shuffledSentence += " ";
            }
            shuffledSentence += shuffleUTF8Word(word);
        }
        return shuffledSentence;
    }

    bool compareSentences(const string &sentence1, const string &sentence2) {
        vector<string> words1 = splitSentenceIntoWords(sentence1);
        vector<string> words2 = splitSentenceIntoWords(sentence2);
        if (words1.size() != words2.size()) {
            return false;
        }
        for (size_t i = 0; i < words1.size(); ++i) {
            if (words1[i] != words2[i]) {
                return false;
            }
        }
        return true;
    }

    void runClassic() {
        shuffledWord = shuffleUTF8Word(currentWord);
    }

    void runSentence(string str) {
        string answer;
        string shuffledStr = shuffleUTF8Sentence(str);
        cout << "Shuffled: " << shuffledStr << endl;
        cout << "Відгадайте речення: ";
        again2:
        getline(cin, answer, '\n');
        if (compareSentences(str, answer)) {
            cout << "Ви вгадали!!!!" << endl;
        } else {
            cout << "Ви не вгадали. Спробуйте ще раз." << endl;
            goto again2;
        }
    }*/

//    string mixWord() {
//        string shuffled = currentWord;
//        cout << shuffled<< endl
//        srand(time(0)); // Ініціалізація генератора випадкових чисел
//        for (size_t i = 0; i < shuffled.size(); ++i) {
//            size_t j = i + rand() % (shuffled.size() - i);
//            swap(shuffled[i], shuffled[j]);
//            cout << shuffled<< endl;
//        }
//        cout << currentWord << endl;
//        cout << shuffled<< endl;
//        return shuffled;
//    }
};
