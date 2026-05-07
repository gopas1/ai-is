#include <iostream>
using namespace std;

// Function to compute GCD
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Function for modular exponentiation
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Find modular inverse of e mod phi
int modInverse(int e, int phi) {
    for (int d = 1; d < phi; d++) {
        if ((e * d) % phi == 1)
            return d;
    }
    return -1;
}

int main() {
    int p, q, n, phi, e, d;
    long long msg, cipher, decrypted;

    cout << "Enter two prime numbers (p and q): ";
    cin >> p >> q;

    n = p * q;
    phi = (p - 1) * (q - 1);

    // Choose e
    for (e = 2; e < phi; e++) {
        if (gcd(e, phi) == 1)
            break;
    }

    d = modInverse(e, phi);

    cout << "\nPublic Key (e, n): (" << e << ", " << n << ")";
    cout << "\nPrivate Key (d, n): (" << d << ", " << n << ")\n";

    cout << "\nEnter message (number < n): ";
    cin >> msg;

    // Encryption
    cipher = modExp(msg, e, n);
    cout << "Encrypted message: " << cipher << endl;

    // Decryption
    decrypted = modExp(cipher, d, n);
    cout << "Decrypted message: " << decrypted << endl;

    return 0;
}
/* PS C:\Users\com\Desktop\AI,IS\IS> g++ rsa.cpp -o output
PS C:\Users\com\Desktop\AI,IS\IS> ./output
Enter two prime numbers (p and q): 3 11

Public Key (e, n): (3, 33)
Private Key (d, n): (7, 33)

Enter message (number < n): 5
Encrypted message: 26
Decrypted message: 5 */