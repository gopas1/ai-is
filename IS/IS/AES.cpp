#include <iostream>
#include <iomanip>
using namespace std;

#define Nb 4
#define Nk 4
#define Nr 10

unsigned char state[4][4];

// Simple S-box (partial for demo)
unsigned char sbox[256] = {
    // only few values filled, rest identity
    0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,
    0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76
};

// Substitute bytes
void SubBytes() {
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            state[i][j] = sbox[state[i][j] % 16]; // simplified
}

// Shift rows
void ShiftRows() {
    unsigned char temp;

    // Row 1
    temp = state[1][0];
    state[1][0] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[1][3];
    state[1][3] = temp;

    // Row 2
    swap(state[2][0], state[2][2]);
    swap(state[2][1], state[2][3]);

    // Row 3
    temp = state[3][3];
    state[3][3] = state[3][2];
    state[3][2] = state[3][1];
    state[3][1] = state[3][0];
    state[3][0] = temp;
}

// AddRoundKey (simple XOR)
void AddRoundKey(unsigned char key[16]) {
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            state[j][i] ^= key[i*4 + j];
}

// Print state
void printState() {
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++)
            cout << hex << setw(2) << setfill('0') << (int)state[i][j] << " ";
        cout << endl;
    }
}

// AES Encrypt (simplified)
void AES_Encrypt(unsigned char input[16], unsigned char key[16]) {

    // Load input into state
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            state[j][i] = input[i*4 + j];

    AddRoundKey(key);

    for(int round=1; round<=Nr; round++) {
        SubBytes();
        ShiftRows();
        AddRoundKey(key);
    }

    cout << "\nEncrypted (hex):\n";
    printState();
}

int main() {
    unsigned char input[16], key[16];

    cout << "Enter 16 characters plaintext: ";
    cin.getline((char*)input, 17);

    cout << "Enter 16 characters key: ";
    cin.getline((char*)key, 17);

    AES_Encrypt(input, key);

    return 0;
}
/* 
    PS C:\Users\com\Desktop\AI,IS\IS> g++ AES.cpp -o output
PS C:\Users\com\Desktop\AI,IS\IS> .\output.exe
Enter 16 characters plaintext: abcdefghijklmnop
Enter 16 characters key: hello234567890

Encrypted (hex):
69 6e 9e 92 
0e e5 1d 9b 
10 44 40 63 
1b f1 44 f2 
 */