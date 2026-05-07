# Information Security (IS) Assignments

This repository contains fully functional C++ and Java implementations of fundamental cryptographic algorithms. The programs trace the evolution of data security from basic ASCII bit-level manipulation to classical ciphers, symmetric-key block ciphers, public-key exchanges, and modern cryptographic message digests.

---

## 1. Bitwise String Operations (`assign1.cpp`)

**Theory**:
At the lowest level, encryption involves manipulating the binary representation of data. Bitwise operators—specifically `AND` (`&`) and `XOR` (`^`)—allow precise control over individual bits. Masking an ASCII character with `127` (`0x7F` or `01111111` in binary) strips the most significant bit, ensuring the output remains a valid standard ASCII character (primarily used for printable outputs and data normalization). XOR is the backbone of stream ciphers due to its reversible property: `(A ^ B) ^ B = A`.

**Implementation**:

- **Variables & Scope**: The code defines a `char` array or `std::string` initialized to `"Hello World"`.
- **Looping**: A `for` loop iterates over each character in the string sequentially.
- **Operations**: Inside the loop, the program computes `char & 127` and `char ^ 127` using C++ bitwise operators.
- **Output Formatting**: The modified character values are printed directly to `std::cout` (cast to integers if control characters are produced) to visualize the exact numerical or character transformation produced by the bitwise masks.

---

## 2. Transposition Cipher (`assign2.cpp`)

**Theory**:
A Transposition Cipher avoids changing the alphabet (like a Caesar cipher) and instead scrambles the positions of the characters. In a Columnar Transposition, the plain text is written into a conceptual 2-dimensional grid from left to right. Once the grid is filled, the ciphertext is read top-to-bottom, but the columns are selected in an order defined by an alphabetical or numerical keyword.

**Implementation**:

- **Grid Construction**: The code calculates the number of columns (length of the key) and the required rows (`ceil(message.length() / key.length())`).
- **Padding**: If the message length is not a perfect multiple of the columns, a padding character (like `'_'` or `~`) is appended to the string.
- **Encryption Process**: The code populates a `std::vector<std::string>` or an equivalent 2D matrix structure row-by-row. To determine the read order, the key characters are mapped to their original indices, and then the key is sorted. The algorithm iterates through the sorted key indices, extracting the corresponding vertical column from the matrix to build the final encrypted string.
- **Decryption Process**: It calculates the grid boundaries again. Since the cipher is linear, it systematically injects characters back into the vertical columns according to the sorted keyword index order, and then reads the grid left-to-right to reconstruct the plaintext.

---

## 3. Data Encryption Standard (DES) (`assign3.cpp`)

**Theory**:
DES is a symmetric-key algorithm utilizing a Feistel Network architecture. It operates on 64-bit data blocks and uses a 56-bit key. The 64 bits are subjected to an Initial Permutation (IP). Then, the block is split into two 32-bit halves ($L_0$ and $R_0$). Over 16 rounds, the right half is expanded to 48 bits, XORed with a 48-bit subkey, passed through 8 substitution boxes (S-boxes) which crush it back to 32 bits, and permuted (P-Box). The result is XORed with the left half, and the halves swap. Finally, the halves are combined and pass through a Final Permutation (FP) $IP^{-1}$.

**Implementation**:

- **Data Structures**: C++ `std::bitset<64>` or arrays of booleans represent the blocks and keys.
- **Key Schedule**: The 64-bit initial key goes through PC-1 to yield 56 bits. A loop runs 16 times, performing circular left shifts (1 or 2 positions depending on the round) on the $C$ and $D$ 28-bit halves, followed by permutation PC-2 to extract the 48-bit round subkeys.
- **Feistel Loop (16 Rounds)**: The 64-bit plaintext is split. In each round:
  - The 32-bit $R$ array is expanded using the predefined Expansion (`E`) array to 48 bits.
  - An `XOR` is evaluated against the 48-bit round subkey.
  - The 48 bits are chunked into 6-bit blocks. The first and last bit determine the Row, and the inner 4 bits determine the Column to dynamically look up the corresponding 4-bit value in the static 2D `S-Box` arrays.
  - The resulting 32 bits are shuffled via the `P` array and XORed with the $L$ half.
- **Post-processing**: After 16 iterations (and preventing a final swap), the bits are passed through the Final Permutation lookup table to generate the ciphertext block.

---

## 4. Advanced Encryption Standard (AES) (`assign4.cpp`)

**Theory**:
AES is a Substitution-Permutation Network (SPN) rather than a Feistel cipher. It natively handles 128-bit block sizes utilizing a 4x4 byte matrix termed the "State". The cipher executes 10 rounds (for a 128-bit key) comprising four distinct invertable steps:

1. `SubBytes`: Byte-by-byte non-linear substitution using a static Rijndael S-box.
2. `ShiftRows`: Circular shifting of the matrix rows (row 0 shifts 0, row 1 shifts 1, etc.).
3. `MixColumns`: Mixing columns mathematically utilizing Galois Field multiplication $GF(2^8)$.
4. `AddRoundKey`: Bitwise XORing the state matrix with the 128-bit scheduled round key.

**Implementation**:

- **State Matrix**: The 16-byte plaintext is explicitly mapped into an `unsigned char state[4][4]` array (Column-major order).
- **Key Expansion**: The core key is expanded into a 176-byte array (comprising 11 distinct 16-byte keys for rounds 0 through 10) utilizing the `Rcon` (round constants) array and S-box substitutions.
- **Encryption Core Loop**:
  - An initial `AddRoundKey` (`XOR`) is applied.
  - A loop runs for 9 iterations driving: `SubBytes()` (direct array lookup), `ShiftRows()` (buffer swapping characters sequentially), `MixColumns()` (invoking an auxiliary Galois field multiplication function using $xtime$), and `AddRoundKey()`.
  - Round 10 executes similarly but explicitly omits the `MixColumns()` function invocation.
- **Mathematical Helpers**: Implementing `MixColumns` requires custom utility functions to handle multiplication by `0x02` and `0x03` in $GF(2^8)$ involving conditional bitwise XORs with `0x1B` if overflow occurs.

---

## 5. RSA Public-Key Cryptography (`assign5.cpp`)

**Theory**:
RSA relies on the computational difficulty of factoring massively large prime numbers.

1. Select two large primes $P$ and $Q$.
2. Calculate the Modulus: $N = P \times Q$.
3. Calculate Euler's Totient: $\phi = (P-1) \times (Q-1)$.
4. Choose an encryption exponent $e$ such that $1 < e < \phi$ and $\gcd(e, \phi) = 1$.
5. Derive the decryption exponent $d$ such that $(d \times e) \mod \phi = 1$.

- Ciphertext: $C = M^e \mod N$.
- Plaintext: $M = C^d \mod N$.

**Implementation**:

- **Auxiliary Functions**: The C++ program implements a `gcd(a, b)` function to verify coprimes, and an `extended_euclidean(e, phi)` or iterative loop to locate the multiplicative modular inverse for evaluating private key $d$.
- **Modular Exponentiation**: Because $M^e$ can cause massive buffer overflows in C++, the code implements an optimized `powerMod(base, exponent, modulus)` function. It uses the "exponentiation by squaring" tactic, taking the base, multiplying it, and subsequently applying `% N` in a bitwise `while(exp > 0)` loop.
- **Execution**: Program prompts the user to input $P$ and $Q$. It mathematically finds $e$, computes $d$, prints the Public $(e, N)$ and Private $(d, N)$ keys, asks for an integer message $M$, and successfully prints the resultant $C$ and decrypted $M$.

---

## 6. Diffie-Hellman Key Exchange (`assign6.cpp`)

**Theory**:
Diffie-Hellman allows two parties to mutually establish a symmetric cryptographic key over an insecure transmission channel. It depends on Discrete Logarithm problem complexities.

- Both parties publicly agree on a giant Prime mod $P$ and its primitive root $G$.
- Alice randomly selects a secret integer $a$, and Bob a secret integer $b$.
- Alice computes public key $A = G^a \mod P$. Bob computes public key $B = G^b \mod P$.
- They swap $A$ and $B$.
- Overlap calculation: Alice derives the shared symmetric key via $S = B^a \mod P$. Bob calculates it via $S = A^b \mod P$.

**Implementation**:

- **Variables**: Represented as large integers (`long long`). The code simulates two isolated parties in a single linear file.
- **Exponentiation Mechanism**: Thoroughly relies on the `powerMod` logical algorithm (repeated squaring with modulo application) to calculate $A$ and $B$ securely without triggering integer bounds overflow limits.
- **Simulation Layout**: The code calculates Alice's chunk, prints it to terminal, calculates Bob's chunk, prints it, and then calculates the local variables $S_A$ and $S_B$. Finally, an `if (S_A == S_B)` assertion validates the success of the secure transfer.

---

## 7. MD5 Message Digest (`assign7.java`, `assign7_scratch.java`)

**Theory**:
MD5 processes an input stream to output a definitive 128-bit (16-byte) hash. The message is first structurally padded by appending a `1` bit (`0x80`), followed by a cascading stream of `0` bits, until the total bit-length evaluates to exactly 64 bits fewer than a multiple of 512. A 64-bit numerical representation of the initial structural length is appended. The 512-bit blocks are parsed through four chaining variables ($A, B, C, D$) manipulated over 64 operations comprising highly non-linear boolean evaluations ($F, G, H, I$), modulo integer additions, bitwise Left-Rotates, and constant application $K[i] = | \sin(i+1) | \times 2^{32}$.

**Implementation**:

- **Native Approach (`assign7.java`)**: Simply uses Java's built-in `java.security.MessageDigest`. After calling `.getInstance("MD5")`, it processes the `.getBytes()` and converts the resulting byte array into a hex string via `BigInteger(1, ...).toString(16)`.
- **Scratch Implementation (`assign7_scratch.java`)**:
  - **Padding Array**: Calculates the required block sizes and injects a `(byte) 128` marker explicitly. It manually breaks down the 64-bit total bit-length identifier and injects it in little-endian order at the tail of the `byte[]` array.
  - **Hashing Outer Loop**: Iterates over the byte array in 64-byte (512-bit) intervals. Each chunk is reformatted into a 16-element integer word array `int[] M`.
  - **Core 64-Round Engine**: Initializes `a0, b0, c0, d0` states. A 64-iteration loop triggers one of 4 formulas (`(B & C) | (~B & D)`, etc.) depending on the index. The states are rigorously updated: `A = B + Integer.rotateLeft((A + func + M[g] + K[i]), shifts)`.
  - **Re-assembly**: Converts the modified 32-bit `a0, b0, c0, d0` integers back into a Little-Endian hexadecimal output via `String.format("%02x...", (byte)a0, ...)` formatting blocks.
