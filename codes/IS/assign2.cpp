#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string encrypt_transposition(string pt, int n, vector<int> perm) {
    for (char &c : pt) if (c == ' ') c = '_';
    while (pt.length() % n != 0) pt += '_';

    string ct = "";
    for (int i = 0; i < n; i++) {
        int col = perm[i];
        for (int j = col; j < pt.length(); j += n) ct += pt[j];
    }
    return ct;
}

string decrypt_transposition(string ct, int n, vector<int> perm) {
    int rows = ct.length() / n;
    string pt(ct.length(), ' '); 
    for (int i = 0; i < n; i++) {
        int col = perm[i];
        for (int r = 0; r < rows; r++) {
            pt[r * n + col] = ct[i * rows + r];
        }
    }
    return pt;
}

int main() {
    while (true) {
        cout << "\n--- Transposition Cipher Menu ---\n";
        cout << "1. Encrypt\n";
        cout << "2. Decrypt (Brute Force Permutations)\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        
        string choice;
        cin >> choice;

        if (choice == "1") {
            string text;
            int n;
            cout << "Enter plaintext: ";
            cin.ignore();
            getline(cin, text);
            cout << "Enter number of columns (n): ";
            cin >> n;
            
            vector<int> perm(n);
            cout << "Enter exact column permutation (0 to " << n - 1 << " separated by space): ";
            for (int i = 0; i < n; i++) cin >> perm[i];
            
            cout << "Encrypted Text: " << encrypt_transposition(text, n, perm) << endl;

        } else if (choice == "2") {
            string text;
            int n;
            cout << "Enter ciphertext: ";
            cin.ignore();
            getline(cin, text);
            cout << "Enter exact number of columns (n): ";
            cin >> n;
            
            vector<int> perm(n);
            for (int i = 0; i < n; i++) perm[i] = i; // 0, 1, 2...
            
            cout << "\n--- Brute Force Results for n = " << n << " ---\n";
            do {
                cout << "Permutation [";
                for (int i = 0; i < n; i++) cout << perm[i] << (i == n-1 ? "" : " ");
                cout << "] : " << decrypt_transposition(text, n, perm) << endl;
            } while (next_permutation(perm.begin(), perm.end()));

        } else if (choice == "3") {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}