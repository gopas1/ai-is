#include <iostream>
#include <string>

using namespace std;

int main() {
    string text = "Hello World";

    cout << "Original : " << text << endl;

    cout << "AND 127 : ";
    for (char ch : text) {
        cout << (ch & 127) << " ";
    }
    cout << endl;

    cout << "XOR 127 : ";
    for (char ch : text) {
        cout << (ch ^ 127) << " ";
    }
    cout << endl;

    return 0;
}
