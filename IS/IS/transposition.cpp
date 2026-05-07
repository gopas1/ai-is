#include <iostream>
#include <string>
using namespace std;

// Encryption
string encrypt(string text, int key) {
    string cipher = "";

    for (int col = 0; col < key; col++) {
        for (int i = col; i < text.length(); i += key) {
            cipher += text[i];
        }
    }
    return cipher;
}

// Decryption
string decrypt(string cipher, int key) {
    int len = cipher.length();
    string text(len, ' ');

    int index = 0;

    for (int col = 0; col < key; col++) {
        for (int i = col; i < len; i += key) {
            text[i] = cipher[index++];
        }
    }
    return text;
}

int main() {
    string text;
    int key;

    cout << "Enter message: ";
    getline(cin, text);

    cout << "Enter key (number of columns): ";
    cin >> key;

    string encrypted = encrypt(text, key);
    cout << "\nEncrypted Text: " << encrypted << endl;

    string decrypted = decrypt(encrypted, key);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}
