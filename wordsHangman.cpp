#include "wordsHangman.h"

WordsHangman::WordsHangman(Account &a, Difficulty d, string fn) : WordsGame(a, d, fn) {}

void WordsHangman::runWordsHangman() {
    int count = 2;
    string words = api.apiRequest(
            "Ми граємо в слова українською мовою. Дай мені рандомних 15 рандомних іменників через пробіл, без коми, нічого крім цього не пиши. Слова повинні бути не більше за 10 символів. Уникай повторень. Кожне слово повинно починатись з великої літери");
    again3:
    ofstream fout("input.txt");
    fout << words << endl;
    runGame();
    int attempts = getAttempts();
    vector<string> currentWordChars = splitUTF8String(currentWord);
    vector<string> guessedWord(currentWordChars.size(), "-");
    unordered_set<string> guessedLetters;
    string hint = "-";
    again:
    int credits = account.getCredits();
    string guessedWordStr;
    for (const auto &ch : guessedWord) {
        guessedWordStr += ch;
    }
    view.printCurrentAttemptTable(guessedWordStr, attempts, hint, credits);

    string input;
    cout << "Введи букву, або \"підказка\": ";
    cin >> input;

    if (input == "підказка") {
        if (credits >= 25) {
            hint = api.apiRequest(
                    "Ми граємо в шибеницю. Зроби підказку українською мовою до 35 символів до слова " + currentWord);
            account.setCredits(credits - 25);
        } else {
            cout
                    << "⚠\uFE0F⚠\uFE0F⚠\uFE0FНа жаль, у вас недостатньо кредитів.😘😘😘😆😆😆:-):-)^_^(┬┬﹏┬┬)(┬┬﹏┬┬)(┬┬﹏┬┬)(╯°□°）╯︵ ┻━┻(╯°□°）╯︵ ┻━┻(╯°□°）╯︵ ┻━┻⚠\uFE0F⚠\uFE0F⚠\uFE0F"
                    << endl;
        }
        goto again;
    }

    vector<string> utf8Chars = splitUTF8String(input);
    if (utf8Chars.size() != 1) {
        cout << "Будь ласка, введіть тільки одну букву." << endl;
        goto again;
    }

    string guess = utf8Chars[0];
    if (guessedLetters.count(guess)) {
        cout << "Ви вже вгадували цю букву. Спробуйте ще раз." << endl;
        goto again;
    }

    guessedLetters.insert(guess);
    bool correctGuess = false;
    for (size_t i = 0; i < currentWordChars.size(); ++i) {
        if (currentWordChars[i] == guess) {
            guessedWord[i] = guess;
            correctGuess = true;
        }
    }

    if (!correctGuess) {
        attempts--;
        cout << "Неправильна відповідь! Залишилось спроб: " << attempts << endl;
    }

    guessedWordStr.clear();
    for (const auto &ch : guessedWord) {
        guessedWordStr += ch;
    }

    if (guessedWordStr == currentWord) {
        winGame();
    } else if (attempts == 0) {
        cout << "Ви програли! Правильна відповідь: " << currentWord << endl;
        account.endGame(false, credits);
    } else {
        goto again;
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


vector<string> WordsHangman::splitUTF8String(const string &str) {
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