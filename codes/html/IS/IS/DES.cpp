#include <iostream>
#include <string>
using namespace std;

/*
 * SIMPLIFIED DES (Feistel Network Demonstration)
 * Theory: Data Encryption Standard (DES) is a symmetric-key block cipher based on the Feistel structure.
 * Real DES Uses: 64-bit plaintext block, 56-bit key, 16 rounds, and complex S-Boxes (Substitution).
 * This program is a simplified "Mock DES" to demonstrate the core Feistel mechanic using:
 * - 8-bit plaintext, 4-bit key, and 2 rounds.
 */

// Function to perform Bitwise XOR on binary strings
string XOR(string a, string b) {
    string result = "";
    for (int i = 0; i < a.size(); i++) {
        // If bits are same -> '0', if different -> '1'
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

/* 
 * Round Function (F-function)
 * In real DES, this is complex (Expansion, XOR with key, S-boxes, Permutation).
 * Here, it's simplified to just returning the XOR of the right half and the key.
 */
string roundFunction(string right, string key) {
    return XOR(right, key);  // simplified
}

/*
 * The core of the Feistel Network:
 * Next Left = Current Right
 * Next Right = Current Left XOR F(Current Right, Key)
 */
void feistelRound(string &left, string &right, string key) {
    string temp = right;
    // XOR the left half with the result of the Round Function applied to the right half
    right = XOR(left, roundFunction(right, key));
    left = temp; // Swap halves
}

// Encryption
string encrypt(string plaintext, string key) {
    // Split the 8-bit plaintext into two 4-bit halves
    string left = plaintext.substr(0, 4);
    string right = plaintext.substr(4, 4);

    // Apply 2 rounds of the Feistel network (Real DES uses 16)
    for (int i = 0; i < 2; i++) {  
        feistelRound(left, right, key);
    }

    // FIX: A true Feistel cipher requires swapping the halves back after the final round
    return right + left; // Return swapped halves to complete encryption symmetrically
}

// Decryption
string decrypt(string ciphertext, string key) {
    // Split the 8-bit ciphertext into halves
    string left = ciphertext.substr(0, 4);
    string right = ciphertext.substr(4, 4);

    /* 
     * In a Feistel cipher, decryption is the exact same process as encryption, 
     * but the subkeys are used in reverse order. Since our key is static here, 
     * we just run the rounds again. 
     */
    for (int i = 0; i < 2; i++) {  
        feistelRound(left, right, key);
    }

    // FIX: Just like encryption, swap the halves back after the final round
    return right + left;
}

int main() {
    string plaintext, key;

    /*
     * DRY RUN EXAMPLE (With fixed final swap!):
     * Input: Plaintext = 10110110, Key = 1111
     * 
     * ENCRYPTION:
     * Initial: Left = 1011, Right = 0110
     * 
     * Round 1: 
     *   Temp = 0110
     *   F(Right, Key) = XOR(0110, 1111) = 1001
     *   New Right = XOR(Left, 1001) = XOR(1011, 1001) = 0010
     *   New Left = Temp = 0110
     *   Result after R1 -> Left = 0110, Right = 0010
     * 
     * Round 2: 
     *   Temp = 0010
     *   F(Right, Key) = XOR(0010, 1111) = 1101
     *   New Right = XOR(Left, 1101) = XOR(0110, 1101) = 1011
     *   New Left = Temp = 0010
     *   Result after R2 -> Left = 0010, Right = 1011
     * 
     * Final Swap: Swap Left and Right one last time -> Left = 1011, Right = 0010
     * Encrypted Output: 10110010
     * 
     * DECRYPTION:
     * Initial: Left = 1011, Right = 0010
     * 
     * Round 1:
     *   Temp = 0010
     *   F(Right, Key) = XOR(0010, 1111) = 1101
     *   New Right = XOR(Left, 1101) = XOR(1011, 1101) = 0110
     *   New Left = Temp = 0010
     *   Result after R1 -> Left = 0010, Right = 0110
     * 
     * Round 2:
     *   Temp = 0110
     *   F(Right, Key) = XOR(0110, 1111) = 1001
     *   New Right = XOR(Left, 1001) = XOR(0010, 1001) = 1011
     *   New Left = Temp = 0110
     *   Result after R2 -> Left = 0110, Right = 1011
     * 
     * Final Swap: Swap Left and Right one last time -> Left = 1011, Right = 0110
     * Decrypted Output: 10110110 (Matches original plaintext!)
     */

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