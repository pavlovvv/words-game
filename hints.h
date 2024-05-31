#include <iostream>
#include <string>

using namespace std;

class Hints {
    string currentHint;
public:
    string show() {
        return currentHint;
    }

    void setHint() {
        currentHint = "sdsd";
    }
};
