#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <algorithm>

using namespace std;

class WordsSentence : public WordsGame {

public:
    WordsSentence(Account &a, Mode m, Difficulty d, string fn) : WordsGame(a, m, d, fn) {}

    void runWordsSentence() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        API api;
        again3:
        string currentSentence = api.apiRequest(
                "Attention! Avoid punctuation. We are playing a word game in Ukrainian. Give me one random sentence of no more than 5 words. ");
        //cout << currentSentence << endl;
        /*ofstream fout("input.txt");
        fout << words << endl;*/
        currentSentence.pop_back();
        runGame();
        string shuffledSentence = shuffleUTF8Sentence(currentSentence);
        int attempts = getAttempts();
        string hint = "-";
        again:
        int credits = account.getCredits();
//        cin.clear();
        view.printCurrentAttemptTable(shuffledSentence, attempts, hint, credits);

        string inputsentence;
        cout << "Введіть речення, або \"підказка\": ";
//        cin.clear();
        getline(cin, inputsentence);

        if (compareSentences(inputsentence, "підказка")) {
            if (credits >= 25) {
                hint = api.apiRequest(
                        "Ми граємо в слова. Зроби підказку українськую мовою до 35 символів до речення: " +
                        currentSentence);
                account.setCredits(credits - 25);
            } else {
                cout
                        << "⚠\uFE0F⚠\uFE0F⚠\uFE0FНа жаль, у вас недостатньо кредитів. Купити їх можна, задонативши на карту 5355571113731129. Після донату пишете в ТГ за номером 0508641813, кидаєте скрін оплати. 100 кредитів = 100грн. Після підтвердження оплати кредити будуть додані на акаунт. Колись.😘😘😘😆😆😆:-):-)^_^(┬┬﹏┬┬)(┬┬﹏┬┬)(┬┬﹏┬┬)(╯°□°）╯︵ ┻━┻(╯°□°）╯︵ ┻━┻(╯°□°）╯︵ ┻━┻⚠\uFE0F⚠\uFE0F⚠\uFE0F"
                        << endl;
            }
            goto again;
        }
        if (compareSentences(inputsentence, currentSentence)) {
            cout << "Ви вгадали!!!!" << endl;
            if (difficulty == Easy) {
                account.endGame(true, credits + 5);
            } else if (difficulty == Medium) {
                account.endGame(true, credits + 15);
            } else {
                account.endGame(true, credits + 25);
            }
        } else {
            if (attempts == 1) {
                cout << "Ви програли! Лошара, правильна віддповідь: " << currentSentence << endl;
                account.endGame(false, credits);
            } else {
                cout << "Ви не вгадали. Спробуйте ще раз." << endl;
                attempts--;
                goto again;
            }
        }
        string choice;
        cout << "Чи бажаєте ви продовжити? (yes/no): ";
        getline(cin, choice);
        if (tolower(choice[0]) == 'y') {
            goto again3;
        }
    }

    vector<string> splitUTF8String(const string &str) {
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
};

