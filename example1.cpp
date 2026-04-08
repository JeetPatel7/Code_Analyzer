#include <iostream>
#include <string>
using namespace std;

int globalVar = 0;

void printMessage(string msg) {
    cout << "Message: " << msg << endl
}

int main() {
    int x = 10;
    int y = 20;

    if (x > y) {
        cout << "X is greater" << endl;
    }
    else
        cout << "Y is greater" << endl;

    // using goto (bad practice)
    goto skip;
    cout << "This line is skipped\n";
    skip:

    int* ptr = new int(5);
    cout << "Pointer value: " << *ptr << endl;

    string longVariableName = "This is a very long line of code that goes beyond eighty characters limit easily";

    delete ptr;
    return 0;
}