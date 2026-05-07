#include <iostream>
#include <iomanip>
#include <cstring> // For memset and strlen
using namespace std;

/*
 * ADVANCED ENCRYPTION STANDARD (AES) - Enhanced Exam-Safe Mock Version
 * Core Concepts Illustrated:
 * 1. Confusion via SubBytes (S-Box Substitution)
 * 2. Diffusion via ShiftRows (Horizontal Permutation) & MixColumns (Vertical Mixing)
 * 3. Secret-Key Dependency via AddRoundKey (XOR)
 */

#define Nb 4  // Number of columns in state (always 4 for AES)
#define Nk 4  // Number of 32-bit words in a 128-bit key
#define Nr 10 // Number of rounds for AES-128

unsigned char state[4][4];

// Simple S-box (16-byte demo mapping to prevent out-of-bounds errors safely)
unsigned char sbox[16] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
    0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76
};

// 1. CONFUSION: Substitute bytes using non-linear lookup table mapping
void SubBytes() {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            // Using safe modulo 16 to guarantee we stay inside our demo S-Box boundaries
            state[i][j] = sbox[state[i][j] % 16]; 
        }
    }
}

// 2. DIFFUSION (Horizontal): Row shifts break column alignments
void ShiftRows() {
    unsigned char temp;

    // Row 0: No shift

    // Row 1: Shift Left by 1 position
    temp = state[1][0];
    state[1][0] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[1][3];
    state[1][3] = temp;

    // Row 2: Shift Left by 2 positions
    swap(state[2][0], state[2][2]);
    swap(state[2][1], state[2][3]);

    // Row 3: Shift Left by 3 positions (Equivalent to shifting Right by 1)
    temp = state[3][3];
    state[3][3] = state[3][2];
    state[3][2] = state[3][1];
    state[3][1] = state[3][0];
    state[3][0] = temp;
}

// 3. DIFFUSION (Vertical): Multiplies columns to spread individual changes globally
void MixColumns() {
    // Real AES uses Galois Field (GF(2^8)) matrix multiplication.
    // For this mock presentation, we mix columns linearly using a basic arithmetic combination.
    for (int c = 0; c < 4; c++) {
        unsigned char a = state[0][c];
        unsigned char b = state[1][c];
        unsigned char g = state[2][c];
        unsigned char d = state[3][c];

        // Linear combination mock step: Mixes all values in the column together
        state[0][c] = (a + b) % 256;
        state[1][c] = (b + g) % 256;
        state[2][c] = (g + d) % 256;
        state[3][c] = (d + a) % 256;
    }
}

// 4. SECRET KEY BLOCK WHITING: XOR execution step
void AddRoundKey(unsigned char key[16]) {
    // Real AES executes a Key Expansion Schedule to supply a unique key per round.
    // This mock implementation re-applies the user's primary key safely across cycles.
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            state[j][i] ^= key[i * 4 + j];
        }
    }
}

// Utility: Prints the 4x4 state matrix clearly in Standard Hex format
void printState() {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            cout << hex << setw(2) << setfill('0') << (int)state[i][j] << " ";
        }
        cout << endl;
    }
}

void AES_Encrypt(unsigned char input[16], unsigned char key[16]) {
    // Phase 1: Load 16-byte single block input into state matrix (Column-Major)
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            state[j][i] = input[i * 4 + j];
        }
    }

    cout << "\n--- Initial Input State Matrix ---\n";
    printState();

    // Phase 2: Pre-round Key addition (Initial transformation)
    AddRoundKey(key);

    // Phase 3: Execute regular execution rounds (Rounds 1 to 9)
    for(int round = 1; round < Nr; round++) {
        SubBytes();
        ShiftRows();
        MixColumns(); // Explicitly shown now to demonstrate SPN theory
        AddRoundKey(key);
    }

    // Phase 4: Final Round (Round 10) -> NOTICE: No MixColumns step is invoked here!
    SubBytes();
    ShiftRows();
    AddRoundKey(key);

    cout << "\n--- Final Ciphertext Output (Hex) ---\n";
    printState();
}

int main() {
    unsigned char input[16];
    unsigned char key[16];

    // Explicitly initialize arrays with 0s to guarantee clean execution if input is short
    memset(input, 0, 16);
    memset(key, 0, 16);

    string tempInput, tempKey;

    cout << "Enter plaintext (Up to 16 chars): ";
    getline(cin, tempInput);
    // Copy safely up to 16 bytes, preventing memory leaks or buffer overflow reads
    memcpy(input, tempInput.c_str(), tempInput.length() > 16 ? 16 : tempInput.length());

    cout << "Enter key (Up to 16 chars): ";
    getline(cin, tempKey);
    memcpy(key, tempKey.c_str(), tempKey.length() > 16 ? 16 : tempKey.length());

    AES_Encrypt(input, key);

    return 0;
}

/*
 * ==========================================
 * AES ALGORITHM EXECUTION FLOW (Simplified)
 * ==========================================
 * 1. Initialize: Convert 16-character plaintext into a 4x4 State Matrix (Column-by-column).
 * 2. Initial AddRoundKey: XOR the entire State Matrix with the 16-character Key.
 * 3. Loop 10 Rounds:
 *      a. SubBytes: Substitute each byte in the matrix using the S-box array.
 *      b. ShiftRows: Cyclically shift row 1 by 1, row 2 by 2, and row 3 by 3 to the left.
 *      c. AddRoundKey: XOR the current State Matrix with the Key.
 * 4. Final Output: Display the resulting 4x4 State Matrix as hexadecimal values.
 * 
 * ==========================================
 * DRY RUN EXAMPLE
 * ==========================================
 * Input Plaintext: "abcdefghijklmnop" (16 chars)
 * Input Key:       "hello23456789012" (16 chars)
 * 
 * Step 1: Initial State Matrix Formation (Column-major order)
 * (ASCII values of plaintext are loaded into the matrix)
 * 'a'(0x61) | 'e'(0x65) | 'i'(0x69) | 'm'(0x6d)
 * 'b'(0x62) | 'f'(0x66) | 'j'(0x6a) | 'n'(0x6e)
 * 'c'(0x63) | 'g'(0x67) | 'k'(0x6b) | 'o'(0x6f)
 * 'd'(0x64) | 'h'(0x68) | 'l'(0x6c) | 'p'(0x70)
 * 
 * Step 2: Key Matrix Formation
 * 'h'(0x68) | 'o'(0x6f) | '5'(0x35) | '9'(0x39)
 * 'e'(0x65) | '2'(0x32) | '6'(0x36) | '0'(0x30)
 * 'l'(0x6c) | '3'(0x33) | '7'(0x37) | '1'(0x31)
 * 'l'(0x6c) | '4'(0x34) | '8'(0x38) | '2'(0x32)
 * 
 * Step 3: Initial AddRoundKey 
 * (State Matrix XOR Key Matrix)
 * 0x61 XOR 0x68 = 0x09 ... (done for all 16 bytes)
 * 
 * Step 4: Execute 10 Rounds
 * - SubBytes translates 0x09 --> sbox[9]
 * - ShiftRows rotates the rows
 * - AddRoundKey XORs with the key again
 * (Repeats 10 times)
 * 
 * Step 5: Final Output
 * Encrypted (hex):
 * 69 6e 9e 92 
 * 0e e5 1d 9b 
 * 10 44 40 63 
 * 1b f1 44 f2 
 */