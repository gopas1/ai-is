#include <iostream>

using namespace std;

// Function to find the Greatest Common Divisor (GCD)
long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

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
    cout << "--- RSA Algorithm ---" << endl;

    long long p, q;
    cout << "Enter first prime number (p): ";
    cin >> p;
    cout << "Enter second prime number (q): ";
    cin >> q;

    // Calculate n and Euler's Totient function (phi)
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    cout << "Calculated n = " << n << ", phi(n) = " << phi << endl;

    // Find Public Key 'e' such that 1 < e < phi and gcd(e, phi) == 1
    long long e = 2;
    while (e < phi) {
        if (gcd(e, phi) == 1) break;
        e++;
    }
    cout << "\nPublic key (e, n): (" << e << ", " << n << ")" << endl;

    // Find Private Key 'd' such that (d * e) % phi == 1
    long long d = 1;
    while ((d * e) % phi != 1) {
        d++;
    }
    cout << "Private key (d, n): (" << d << ", " << n << ")" << endl;

    // Message Input
    long long msg;
    cout << "\nEnter a numeric message to encrypt (must be less than " << n << "): ";
    cin >> msg;

    // Encryption: c = (m ^ e) % n
    long long cipher = modPow(msg, e, n);
    cout << "Encrypted message (Ciphertext): " << cipher << endl;

    // Decryption: m = (c ^ d) % n
    long long decrypted = modPow(cipher, d, n);
    cout << "Decrypted message (Plaintext): " << decrypted << endl;

    return 0;
}