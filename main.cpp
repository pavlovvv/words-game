#include <iostream>
#include "account.h"

using namespace std;

int main() {
    string name;
    account account;
    cout << "Вітаю у грі в слова! Будь ласка, введіть ваше ім'я: ";
    cin >> name;
    if (account.isNameTaken(name)){
        cout << "Вітаю в програмі";
    }
    else {

    }
    return 0;
}
