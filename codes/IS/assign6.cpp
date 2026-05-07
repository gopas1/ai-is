#include <iostream>

using namespace std;

// Function for Modular Exponentiation: (base^exp) % mod
long long modPow(long long base, long long exp, long long mod) {
    long long res = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod; // If exp is odd, multiply base
        exp = exp >> 1;                             // Divide exp by 2
        base = (base * base) % mod;                 // Square the base
    }
    return res;
}

int main() {
    cout << "--- Diffie-Hellman Key Exchange ---" << endl;

    long long P, G;
    cout << "Enter a public prime number (P): ";
    cin >> P;
    cout << "Enter a primitive root of P (G): ";
    cin >> G;

    long long a, b;
    cout << "\nEnter Alice's private key (a): ";
    cin >> a;
    cout << "Enter Bob's private key (b): ";
    cin >> b;

    // Alice calculates her public key x: (G^a) % P
    long long x = modPow(G, a, P);
    cout << "\nAlice's generated public key (x) sent to Bob: " << x << endl;

    // Bob calculates his public key y: (G^b) % P
    long long y = modPow(G, b, P);
    cout << "Bob's generated public key (y) sent to Alice:   " << y << endl;

    // Alice generates the shared secret key using Bob's public key y: (y^a) % P
    long long ka = modPow(y, a, P);
    
    // Bob generates the shared secret key using Alice's public key x: (x^b) % P
    long long kb = modPow(x, b, P);

    cout << "\n--- Shared Secret Calculation ---" << endl;
    cout << "Secret key calculated by Alice: " << ka << endl;
    cout << "Secret key calculated by Bob:   " << kb << endl;

    if (ka == kb) {
        cout << "\nKey Exchange Successful! Both share the secret key: " << ka << endl;
    } else {
        cout << "\nError: Keys do not match!" << endl;
    }

    return 0;
}

/*
 * HOW DIFFIE-HELLMAN KEY EXCHANGE WORKS:
 * 
 * 1. Setup: Alice and Bob publicly agree on a prime number (P) and its primitive root (G).
 * 
 * 2. Private Keys: 
 *    - Alice chooses a secret private key (a).
 *    - Bob chooses a secret private key (b).
 *    (These are never shared with anyone)
 * 
 * 3. Public Keys (Transmission):
 *    - Alice calculates her public key 'x' = (G^a) % P and sends it to Bob.
 *    - Bob calculates his public key 'y' = (G^b) % P and sends it to Alice.
 * 
 * 4. Shared Secret Calculation:
 *    - Alice receives 'y' from Bob and calculates her secret: ka = (y^a) % P.
 *    - Bob receives 'x' from Alice and calculates his secret: kb = (x^b) % P.
 * 
 * 5. The Mathematical Magic:
 *    - Alice's calculation is effectively: ((G^b) % P)^a % P  =>  G^(a*b) % P
 *    - Bob's calculation is effectively:   ((G^a) % P)^b % P  =>  G^(a*b) % P
 *    Because the math resolves to the exact same formula (G^(ab) % P), ka == kb. 
 *    They now share a secure secret key over a public network!
 */