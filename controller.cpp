#include <iostream>
#include <string>
#include "view.h"
#include "difficulty_enum.h"
#include "mode_enum.h"
#include "wordsgame.h"
#include "API.h"
#include "controller.h"

using namespace std;

void Controller:: startGame() {
        while (true) {
        Mode mode;
        Difficulty difficulty;
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


        WordsGame wordsGame(mode, difficulty, "input.txt");

        API api;
        string words = api.apiRequest("Ми граємо в слова українською мовою. Дай мені рандомних 30 іменників через пробіл, без коми, нічого крім цього не пиши. Слова повинні бути не більше за 10 символів. Уникай повторень. Кожне слово повинно починатись з великої літери");
        ofstream fout("input.txt");
        fout << words << endl;
        wordsGame.runGame();
        }
}

