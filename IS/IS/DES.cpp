#include <iostream>
#include <string>
using namespace std;

// Function to perform XOR
string XOR(string a, string b) {
    string result = "";
    for (int i = 0; i < a.size(); i++) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

// Simple round function (not real DES S-box)
string roundFunction(string right, string key) {
    return XOR(right, key);  // simplified
}

// One round of Feistel
void feistelRound(string &left, string &right, string key) {
    string temp = right;
    right = XOR(left, roundFunction(right, key));
    left = temp;
}

// Encryption
string encrypt(string plaintext, string key) {
    string left = plaintext.substr(0, 4);
    string right = plaintext.substr(4, 4);

    for (int i = 0; i < 2; i++) {  // 2 rounds (simplified)
        feistelRound(left, right, key);
    }

    return left + right;
}

// Decryption
string decrypt(string ciphertext, string key) {
    string left = ciphertext.substr(0, 4);
    string right = ciphertext.substr(4, 4);

    for (int i = 0; i < 2; i++) {  // reverse same rounds
        feistelRound(left, right, key);
    }

    return left + right;
}

int main() {
    string plaintext, key;

    cout << "Enter 8-bit binary plaintext: ";
    cin >> plaintext;

    cout << "Enter 4-bit binary key: ";
    cin >> key;

    string cipher = encrypt(plaintext, key);
    cout << "\nEncrypted: " << cipher << endl;

    string decrypted = decrypt(cipher, key);
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}