#include <iostream>
using namespace std;

int main() {
    char *str;
    int size;

    cout << "Enter size of string: ";
    cin >> size;

    str = new char[size + 1];

    cout << "Enter a string: ";
    cin.ignore();
    cin.getline(str, size + 1);

    cout << "\nOriginal String: " << str << endl;

    cout << "\nAfter AND with 127:\n";
    for (int i = 0; str[i] != '\0'; i++) {
        char result = str[i] & 127;
        cout << result;
    }

    cout << "\n\nAfter XOR with 127:\n";
    for (int i = 0; str[i] != '\0'; i++) {
        char result = str[i] ^ 127;
        cout << result;
    }

    delete[] str;
    return 0;
}
/* g++ ANDXOR.cpp -o output 
    ./output */