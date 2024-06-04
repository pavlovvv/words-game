#include "wordsHidden.h"

WordsHidden::WordsHidden(Account &a, Difficulty d, string fn) : WordsGame(a, d, fn) {}

void WordsHidden::runWordsHidden() {
    string words = api.apiRequest(
            "Ми граємо в слова українською мовою. Дай мені рандомних 15 рандомних іменників через пробіл, без коми, нічого крім цього не пиши. Слова повинні бути не більше за 10 символів. Уникай повторень. Кожне слово повинно починатись з великої літери");
    again3:
    ofstream fout("input.txt");
    fout << words << endl;
    runGame();
    shuffledWord = shuffleUTF8Word(currentWord);
    string hint = "-";
    again:
    int credits = account.getCredits();
    view.printCurrentAttemptTable(shuffledWord, getAttempts(), hint, credits);
    string inputword;
    cout << "Введи слово, або \"підказка\": ";
    cin >> inputword;
    if (inputword == "підказка") {
        if (credits >= 25) {
            hint = api.apiRequest(
                    "Ми граємо в слова. Зроби підказку українськую мовою до 35 символів до слова " + currentWord);
            account.setCredits(credits - 25);
        } else {
            cout
                    << "⚠\uFE0F⚠\uFE0F⚠\uFE0FНа жаль, у вас недостатньо кредитів.😘😘😘😆😆😆:-):-)^_^(┬┬﹏┬┬)(┬┬﹏┬┬)(┬┬﹏┬┬)(╯°□°）╯︵ ┻━┻(╯°□°）╯︵ ┻━┻(╯°□°）╯︵ ┻━┻⚠\uFE0F⚠\uFE0F⚠\uFE0F"
                    << endl;
        }
        goto again;
    }
    if (inputword == currentWord) {
        winGame();
    } else {
        if (attempts == 1) {
            cout << "Ви програли! Правильна віддповідь: " << currentWord << endl;
            account.endGame(false, credits);
        } else {
            cout << "Ви не вгадали. Спробуйте ще раз." << endl;
            attempts--;
            goto again;
        }
    }
    count++;
    if (count < 15) {
        string choice;
        cout << "Чи бажаєте ви продовжити? (yes/no): ";
        cin >> choice;
        if (tolower(choice[0]) == 'y') {
            system("clear");
            goto again3;
        }
    }
}

vector<string> WordsHidden::splitUTF8String(const string &str) {
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

string WordsHidden::shuffleUTF8Word(const string &str) {
    vector<string> utf8Chars = splitUTF8String(str);
    random_device rd;
    mt19937 g(rd());
    shuffle(utf8Chars.begin(), utf8Chars.end(), g);
    string shuffledStr;
    int size = utf8Chars.size();
    double k = size / 4.0;
    vector<int> changedIndexes;
    if (k > 0 && k <= 1) {
        changeRandomChar(utf8Chars, changedIndexes, g, 1);
    } else if (k > 1 && k <= 2) {
        changeRandomChar(utf8Chars, changedIndexes, g, 2);
    } else if (k > 2 && k <= 3) {
        changeRandomChar(utf8Chars, changedIndexes, g, 3);
    } else if (k > 3 && k <= 4) {
        changeRandomChar(utf8Chars, changedIndexes, g, 4);
    } else if (k > 4 && k <= 5) {
        changeRandomChar(utf8Chars, changedIndexes, g, 5);
    }
    for (const auto &ch : utf8Chars) {
        shuffledStr += ch;
    }
    return shuffledStr;
}

void WordsHidden::changeRandomChar(vector<string> &utf8Chars, vector<int> &changedIndices, mt19937 &g, int n) {
    for (int i = 0; i < n; i++) {
        uniform_int_distribution<> dis(0, utf8Chars.size() - 1);
        int index;
        do {
            index = dis(g);
        } while (find(changedIndices.begin(), changedIndices.end(), index) != changedIndices.end());
        utf8Chars[index] = "*";
        changedIndices.push_back(index);
    }
}
