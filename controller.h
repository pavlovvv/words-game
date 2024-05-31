#include <iostream>
#include <string>
#include "view.h"
#include "difficulty_enum.h"
#include "mode_enum.h"
#include "wordsgame.h"
#include "wordsClassic.h"

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
        while(true){
            account.getData(account.getName());
            view.menuInteraction(account);
            startGame();
        }
    }


    void startGame() {
        while (true) {
            cout << "\nВиберіть режим (classic/hidden/proverb/sentence/hangman)" << endl;
            cout << "Classic - класичний варіант гри в \"Слова\"" << endl;
            cout << "Hidden - режим, де частина букв замінені на '*'. Цей режим підходить тим, хто вже трохи пограв у класичний режим" << endl;
            cout << "Proverb - режим для тих, хто вважає, що він добре знає прислів'я і приказки." << endl;
            cout << "Sentence - режим для тих, кому гра з одним словом здається нудною. Відгадуйте одразу декілька слів." << endl;
            cout << "Hangman - стара класична гра, де ви вгадуєте які літери є в слові і вгадуєте саме слово, доки шибениця не буде домальована до кінця." << endl;
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
            cout << "Easy - це складність, де у вас є необмежений час. Підходить початківцям." << endl;
            cout << "Medium - складність, де у вас обмежений час (залежить від режиму). Більше підходить для тих, хто вже трохи пограв." << endl;
            cout << "Hard - максимальна складність. В неї важко буде грати навіть досвідченим гравцям. Часу дуже мало, а слів менше не стало." << endl;
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

        if(mode == Classic){
            WordsClassic wordsClassic(account, mode, difficulty, "input.txt");
            wordsClassic.runWordsClassic();
        }

        /*API api;
        string words = api.apiRequest("Ми граємо в слова українською мовою. Дай мені рандомних 30 іменників через пробіл, без коми, нічого крім цього не пиши. Слова повинні бути не більше за 10 символів. Уникай повторень. Кожне слово повинно починатись з великої літери");
        ofstream fout("input.txt");
        fout << words << endl;
        wordsGame.runGame();
        string currentWord = wordsGame.getWord();
        int attempts = wordsGame.getAttempts();
        string hint = "-";
        again:
        int credits = view.getAccountCredits();
        view.printCurrentAttemptTable(wordsGame.getShuffledWord(), attempts, hint, credits);

        string inputword;
        cout << "Введи слово, або \"підказка\": ";
        getline(cin, inputword, ' ');
        if (inputword == "підказка") {
            if (credits >= 25) {
                hint = api.apiRequest("Ми граємо в слова. Зроби підказку українськую мовою до 40 символів до слова " + currentWord);
                view.setAccountCredits(credits-25);
            }
            else {
                cout << "⚠\uFE0F⚠\uFE0F⚠\uFE0FНа жаль, у вас недостатньо кредитів. Купити їх можна, задонативши на карту 5355571113731129. Після донату пишете в ТГ за номером 0508641813, кидаєте скрін оплати. 100 кредитів = 100грн. Після підтвердження оплати кредити будуть додані на акаунт. Колись.😘😘😘😆😆😆:-):-)^_^(┬┬﹏┬┬)(┬┬﹏┬┬)(┬┬﹏┬┬)(╯°□°）╯︵ ┻━┻(╯°□°）╯︵ ┻━┻(╯°□°）╯︵ ┻━┻⚠\uFE0F⚠\uFE0F⚠\uFE0F" << endl;
            }
            goto again;
        }
        if (inputword == currentWord) {
            cout << "Ви вгадали!!!!" << endl;
            if(difficulty == Easy){
                view.setAccountCredits(credits+5);
            }else if(difficulty == Medium){
                view.setAccountCredits(credits+15);
            }else view.setAccountCredits(credits+25);

        } else {
            if (attempts == 1) {
                cout << "Ви програли! Лошара" << endl;
            }
            else {
                cout << "Ви не вгадали. Спробуйте ще раз." << endl;
                attempts--;
                goto again;
            }
        }*/
    }
};