#include "wordsSentence.h"

WordsSentence::WordsSentence(Account &a, Difficulty d, string fn) : WordsGame(a, d, fn) {}

void WordsSentence::runWordsSentence() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    again3:
    string currentSentence = api.apiRequest(
            "Attention! Avoid punctuation. We are playing a word game in Ukrainian. Give me one random sentence or proverb of no more than 5 words. ");
    currentSentence.pop_back();
    runGame();
    string shuffledSentence = shuffleUTF8Sentence(currentSentence);
    int attempts = getAttempts();
    string hint = "-";
    again:
    int credits = account.getCredits();
    view.printCurrentAttemptTable(shuffledSentence, attempts, hint, credits);

    string inputsentence;
    cout << "Введіть речення, або \"підказка\": ";
    getline(cin, inputsentence);

    if (compareSentences(inputsentence, "підказка")) {
        string help;
        cout << "Введіть текст для підказки: ";
        getline(cin, help);
        if (credits >= 25) {
            hint = api.apiRequest(
                    "Ми граємо в гру в слоова," + help + " у реченні " + currentSentence);
            account.setCredits(credits - 25);
        } else {
            cout
                    << "⚠\uFE0F⚠\uFE0F⚠\uFE0FНа жаль, у вас недостатньо кредитів.😘😘😘😆😆😆:-):-)^_^(┬┬﹏┬┬)(┬┬﹏┬┬)(┬┬﹏┬┬)(╯°□°）╯︵ ┻━┻(╯°□°）╯︵ ┻━┻(╯°□°）╯︵ ┻━┻⚠\uFE0F⚠\uFE0F⚠\uFE0F"
                    << endl;
        }
        goto again;
    }
    if (compareSentences(inputsentence, currentSentence)) {
        winGame();
    } else {
        if (attempts == 1) {
            cout << "Ви програли! Правильна віддповідь: " << currentSentence << endl;
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
        system("clear");
        goto again3;
    }
}

vector<string> WordsSentence::splitUTF8String(const string &str) {
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


string WordsSentence::shuffleUTF8Word(const string &str) {
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

vector<string> WordsSentence::splitSentenceIntoWords(const string &sentence) {
    vector<string> words;
    istringstream stream(sentence);
    string word;
    while (stream >> word) {
        words.push_back(word);
    }
    return words;
}

string WordsSentence::shuffleUTF8Sentence(const string &sentence) {
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

bool WordsSentence::compareSentences(const string &sentence1, const string &sentence2) {
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