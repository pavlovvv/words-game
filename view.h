#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <iomanip>
#include "account.h"
#include "leaderboard.h"

using namespace std;

class View {
private:
    Leaderboard leaderboard;
public:

    void accountInteraction(Account &account) {
        string name;
        cout << "Вітаю у грі в слова! Будь ласка, введіть ваше ім'я: ";
        cin >> name;
        if (account.getData(name)) {
            cout << "Вітаю в програмі, " << account.getName();
        } else {
            string choice;
            cout << "Користувача не знайдено. Бажаєте створити аккаунт новий аккаунт (yes/no)? ";
            while (true) {
                cin >> choice;
                if (tolower(choice[0]) == 'y') {
                    cout << "Створено аккаунт з ім'ям " << name << endl;
                    account.createAccount(name);
                    break;
                } else if (tolower(choice[0]) == 'n') {
                    cout << "Входжу через режим гостя!";
                    account.enterAsGuest();
                    break;
                } else {
                    cout << "Неправильний ввід. Спробуйте ще раз." << endl;
                    continue;
                }
            }
        }
    }

    void menuInteraction(Account &account) {
        while (true) {
            int choice;
            back:
            cout
                    << "\nОберіть дію: \n1 - Продивитись поточну статистику акаунта\n2 - Переглянути лідерборд \n3 - Почати гру \n4 - Вихід з програми\n";
            cin >> choice;
            switch (choice) {
                case 1:
                    cout << "Ваша статистика: " << endl;
                    printAccountData(account);
                    break;
                case 2:
                    cout << "Лідерборд: " << endl;
                    while (true) {
                        int choice1;
                        cout
                                << "\nОберіть лідерборд: \n1 - За іграми\n2 - За перемогами\n3 - За перемогами підряд\n4 - Повернутися\n";
                        cin >> choice1;
                        switch (choice1) {
                            case 1:
                                leaderboard.printLeaderboard("gamesLeaderboard.txt");
                                break;
                            case 2:
                                leaderboard.printLeaderboard("winsLeaderboard.txt");
                                break;
                            case 3:
                                leaderboard.printLeaderboard("winsInARowLeaderboard.txt");
                                break;
                            case 4:
                                cout << "Ну і уйобуй" << endl;
                                goto back;
                            default:
                                cout << "Такого варіанту не існує. Оберіть із списку вище." << endl;
                                break;
                        }
                    }
                case 3:
                    cout << "Початок гри: " << endl;
                    return;
                case 4:
                    cout << "До побачення! " << endl;
                    exit(0);
                default:
                    cout << "Такого варіанту не існує. Оберіть із списку вище." << endl;
                    break;
            }
        }
    }

    void printAccountData(Account &account) {
        cout << "┌──────────────────┬───────────┬──────────────────┬─────────────┐" << endl;
        cout << "│ " << setw(20) << left << "  Ігор зіграно  "
             << " │ " << setw(8) << " Перемог "
             << " │ " << setw(15) << " Перемог підряд "
             << " │ " << setw(8) << "  Кредити   │" << endl;
        cout << "├──────────────────┼───────────┼──────────────────┼─────────────┤" << endl;
        cout << "│ " << setw(16) << left << account.getGamesCount()
             << " │ " << setw(9) << account.getWins()
             << " │ " << setw(16) << account.getWinsInARow()
             << " │ " << setw(11) << account.getCredits() << " │" << endl;
        cout << "└──────────────────┴───────────┴──────────────────┴─────────────┘" << endl;
    }

    void printCurrentAttemptTable(string shuffledWord, int attempts, string hint, int credits) {
        cout
                << "┌──────────────────────────────────────┬──────────────────────────────────────────────────────────────┬────────────────────┬───────────────────────┐"
                << endl;
        cout
                << "│           Перемішане слово           │                           Підказка                           │  Спроб залишилось  │  Кредитів залишилось  │"
                << endl;
        cout
                << "├──────────────────────────────────────┼──────────────────────────────────────────────────────────────┼────────────────────┼───────────────────────┤"
                << endl;
        cout << "│ " << shuffledWord;
        printSpaces(37 - countUTF8Characters(shuffledWord));
        cout << "│ " << hint;
        printSpaces(61 - countUTF8Characters(hint));
        cout << "│ " << attempts;
        printSpaces(19 - countIntCharacters(attempts));
        cout << "│ " << credits;
        printSpaces(22 - countIntCharacters(credits));
        cout << "│" << endl;
        cout
                << "└──────────────────────────────────────┴──────────────────────────────────────────────────────────────┴────────────────────┴───────────────────────┘"
                << endl;
    }

    void printSpaces(int n) {
        for (int i = 0; i < n; i++) {
            cout << ' ';
        }
    }

    int countUTF8Characters(const string &str) {
        int count = 0;
        for (int i = 0; i < static_cast<int>(str.size());) {
            if ((str[i] & 0x80) == 0x00) {
                i += 1; // 1-byte character (ASCII)
            } else if ((str[i] & 0xE0) == 0xC0) {
                i += 2; // 2-byte character
            } else if ((str[i] & 0xF0) == 0xE0) {
                i += 3; // 3-byte character
            } else if ((str[i] & 0xF8) == 0xF0) {
                i += 4; // 4-byte character
            }
            ++count;
        }
        return count;
    }

    int countIntCharacters(int a) {
        int count = 0;
        if (a == 0) {
            return 1;
        }
        while (a > 0) {
            a /= 10;
            count++;
        }
        return count;
    }
};
