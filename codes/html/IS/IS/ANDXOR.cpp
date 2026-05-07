#include <iostream>
using namespace std;

int main() {
    /* 
     * The problem asks for a string (char pointer) with a value "Hello World".
     * Your original code allowed dynamic user input which is great, 
     * but to perfectly align with the question, we can directly set "Hello World".
     * You can uncomment the dynamic part if your professor prefers dynamic input.
     */
    
    // Using a char pointer with the value 'Hello World' as required by PS
    const char *str = "Hello World";

    /*
    Dynamic input alternative:
    int size;
    cout << "Enter size of string: ";
    cin >> size;
    char *str = new char[size + 1];
    cout << "Enter a string: ";
    cin.ignore();
    cin.getline(str, size + 1);
    */

    cout << "\nOriginal String: " << str << endl;

    /*
     * Bitwise AND operation (&) with 127
     * 127 in binary is 01111111.
     * When we AND any standard ASCII character (value 0-127) with 127, 
     * it remains unchanged because the lowest 7 bits remain intact.
     */
    cout << "\nAfter AND with 127:\n";
    for (int i = 0; str[i] != '\0'; i++) {
        char result = str[i] & 127;
        cout << result;
    }

    /*
     * Bitwise XOR operation (^) with 127
     * XORing with 01111111 flips the bits of the character.
     * This alters the character completely, often converting it into non-printable 
     * or different ASCII characters (basic form of encryption).
     */
    cout << "\n\nAfter XOR with 127:\n";
    for (int i = 0; str[i] != '\0'; i++) {
        char result = str[i] ^ 127;
        cout << result;
    }
    cout << endl;

    // delete[] str; // (Required only if using dynamic input 'new char[]')
    return 0;
}
/* g++ ANDXOR.cpp -o output 
    ./output */