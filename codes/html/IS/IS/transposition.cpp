#include <iostream>
#include <string>
using namespace std;

/*
 * TRANSPOSITION CIPHER (Simple Columnar / Rail Fence)
 * Theory: Transposition ciphers do not change the letters themselves (like substitution does).
 * Instead, they scramble the positions of the letters.
 * Here, we conceptually write the text in rows (where row length = key)
 * and read it column by column to create the ciphertext.
 */

// Encryption
string encrypt(string text, int key) {
    string cipher = "";

    // Loop through each column
    for (int col = 0; col < key; col++) {
        // Start at current column 'col', jump by 'key' to get the next char in the same column
        for (int i = col; i < text.length(); i += key) {
            cipher += text[i];
        }
    }
    return cipher;
}

// Decryption
string decrypt(string cipher, int key) {
    int len = cipher.length();
    // Create a string of the same length filled with spaces
    string text(len, ' ');

    int index = 0;

    // Use the exact same mathematical pattern to figure out where characters belong
    for (int col = 0; col < key; col++) {
        for (int i = col; i < len; i += key) {
            // Write the sequential ciphertext characters into their original 'jumped' positions
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

    // The key here acts as the 'number of columns' in our conceptual grid
    cout << "Enter key (number of columns): ";
    cin >> key;

    string encrypted = encrypt(text, key);
    cout << "\nEncrypted Text: " << encrypted << endl;

    string decrypted = decrypt(encrypted, key);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}
