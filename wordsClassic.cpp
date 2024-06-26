#include "wordsClassic.h"

WordsClassic::WordsClassic(Account &a, Difficulty d, string fn) : WordsGame(a, d, fn) {}

void WordsClassic::runWordsClassic() {
    int count = 2;
    string words = api.apiRequest(
            "Ми граємо в слова українською мовою. Дай мені рандомних 15 рандомних іменників через пробіл, без коми, нічого крім цього не пиши. Слова повинні бути не більше за 10 символів. Уникай повторень. Кожне слово повинно починатись з великої літери");
    again3:
    ofstream fout("input.txt");
    fout << words << endl;
    runGame();
    shuffledWord = shuffleUTF8Word(currentWord);
    int attempts = getAttempts();
    string hint = "-";
    again:
    int credits = account.getCredits();
    view.printCurrentAttemptTable(shuffledWord, attempts, hint, credits);

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

vector<string> WordsClassic::splitUTF8String(const string &str) {
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

string WordsClassic::shuffleUTF8Word(const string &str) {
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