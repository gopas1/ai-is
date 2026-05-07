#include <iostream>
using namespace std;

/*
 * RSA ALGORITHM (Rivest-Shamir-Adleman)
 * Theory: RSA is an asymmetric cryptographic algorithm. This means it uses two different keys:
 * 1. Public Key: Used to encrypt the message. Shared with everyone.
 * 2. Private Key: Used to decrypt the message. Kept completely secret.
 * 
 * The security of RSA relies on the mathematical difficulty of prime factorization.
 * It is easy to multiply two large prime numbers, but extremely difficult for a computer
 * to take the result and figure out what those two original prime numbers were.
 */

// Function to compute GCD (Greatest Common Divisor) using Euclidean algorithm
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Function for modular exponentiation: (base^exp) % mod
// This is used for encryption (msg^e % n) and decryption (cipher^d % n)
// It is written this way to prevent integer overflow when dealing with massive exponents.
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) // If exp is odd, multiply base with result
            result = (result * base) % mod;

        // Divide exp by 2 and square the base
        exp = exp >> 1; 
        base = (base * base) % mod;
    }
    return result;
}

// Find modular inverse (d) of e mod phi
// We need 'd' such that: (e * d) % phi = 1
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

    // STEP 1: Compute n = p * q.
    // 'n' is part of both the public and private keys.
    n = p * q;

    // STEP 2: Compute Euler's Totient Function, phi = (p - 1) * (q - 1).
    // Phi tells us how many numbers are coprime to 'n'.
    phi = (p - 1) * (q - 1);

    // STEP 3: Choose 'e' (encryption key).
    // 'e' must be coprime to phi (meaning their GCD must be 1).
    for (e = 2; e < phi; e++) {
        if (gcd(e, phi) == 1)
            break; // Find the first valid 'e'
    }

    // STEP 4: Compute 'd' (decryption key).
    // 'd' is the modular multiplicative inverse of e (mod phi).
    d = modInverse(e, phi);

    cout << "\nPublic Key (e, n): (" << e << ", " << n << ")";
    cout << "\nPrivate Key (d, n): (" << d << ", " << n << ")\n";

    cout << "\nEnter message (number < n): ";
    cin >> msg;

    // STEP 5: Encrypt -> cipher = msg^e % n
    cipher = modExp(msg, e, n);
    cout << "Encrypted message: " << cipher << endl;

    // STEP 6: Decrypt -> decrypted = cipher^d % n
    decrypted = modExp(cipher, d, n);
    cout << "Decrypted message: " << decrypted << endl;

    return 0;
}

/*
 * ==========================================
 * RSA ALGORITHM EXECUTION FLOW & DRY RUN
 * ==========================================
 * 
 * --- KEY GENERATION ---
 * 1. Choose two primes: Let p = 3, q = 11.
 * 2. Calculate n = p * q
 *    -> n = 3 * 11 = 33.
 * 3. Calculate phi(n) = (p - 1) * (q - 1)
 *    -> phi = (2) * (10) = 20.
 * 4. Choose e: Must be 1 < e < phi, and coprime to phi(20).
 *    -> e = 3. (Since GCD(3, 20) == 1)
 * 5. Calculate d: (e * d) % phi = 1
 *    -> (3 * d) % 20 = 1
 *    -> When d = 7, (3 * 7) % 20 = 21 % 20 = 1.
 *    -> So, d = 7.
 * 
 * Resulting Keys:
 * Public Key (e, n)  = (3, 33)  [Given to everyone]
 * Private Key (d, n) = (7, 33)  [Kept secret]
 * 
 * --- ENCRYPTION ---
 * Let input message (M) = 5.
 * Formula: C = (M^e) % n
 * C = (5^3) % 33
 * C = 125 % 33
 * C = 26
 * -> Encrypted Ciphertext = 26
 * 
 * --- DECRYPTION ---
 * Formula: M = (C^d) % n
 * M = (26^7) % 33
 * M = 8031810176 % 33
 * M = 5
 * -> Decrypted Plaintext = 5
 */