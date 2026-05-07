import java.util.Scanner;

public class assign7_scratch {

    // MD5 specific shift amounts for the 64 operations
    private static final int[] S = {
        7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
        5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
        4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
        6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
    };

    // MD5 Constants (calculated from the sine of integers)
    private static final int[] K = new int[64];
    static {
        for (int i = 0; i < 64; i++) {
            K[i] = (int) (long) ((1L << 32) * Math.abs(Math.sin(i + 1)));
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("--- MD5 Algorithm ---");
        System.out.print("Enter text to hash: ");
        String text = sc.nextLine();
        
        System.out.println("Calculated MD5: " + computeMD5(text.getBytes()));
        sc.close();
    }

    public static String computeMD5(byte[] message) {
        // 1. Initial standard MD5 state variables (A, B, C, D)
        int a0 = 0x67452301;
        int b0 = 0xefcdab89;
        int c0 = 0x98badcfe;
        int d0 = 0x10325476;

        // 2. Padding the message
        int originalLengthBytes = message.length;
        long originalLengthBits = (long) originalLengthBytes * 8;
        
        // Calculate the padding needed to make length % 64 == 56 bytes (448 bits)
        int paddingLength = (56 - (originalLengthBytes % 64) + 64) % 64;
        if (paddingLength == 0) paddingLength = 64; // A single '1' bit is always required

        // Total length = original + padding + 8 bytes (for the 64-bit length)
        byte[] paddedMessage = new byte[originalLengthBytes + paddingLength + 8];
        System.arraycopy(message, 0, paddedMessage, 0, originalLengthBytes);
        
        // Append the '1' bit (0x80 in byte)
        paddedMessage[originalLengthBytes] = (byte) 0x80; 
        
        // Append the 64-bit length in little-endian format at the very end
        for (int i = 0; i < 8; i++) {
            paddedMessage[paddedMessage.length - 8 + i] = (byte) (originalLengthBits >>> (8 * i));
        }

        // 3. Process the padded message in 64-byte (512-bit) blocks
        for (int offset = 0; offset < paddedMessage.length; offset += 64) {
            
            // Break the 64-byte block into 16 32-bit words (little-endian)
            int[] M = new int[16];
            for (int i = 0; i < 16; i++) {
                M[i] = (paddedMessage[offset + 4 * i] & 0xFF) |
                      ((paddedMessage[offset + 4 * i + 1] & 0xFF) << 8) |
                      ((paddedMessage[offset + 4 * i + 2] & 0xFF) << 16) |
                      ((paddedMessage[offset + 4 * i + 3] & 0xFF) << 24);
            }

            int A = a0;
            int B = b0;
            int C = c0;
            int D = d0;

            // 4. Main MD5 Algorithm Loop (64 Operations)
            for (int i = 0; i < 64; i++) {
                int F, g;
                
                if (i < 16) {
                    F = (B & C) | (~B & D);
                    g = i;
                } else if (i < 32) {
                    F = (D & B) | (~D & C);
                    g = (5 * i + 1) % 16;
                } else if (i < 48) {
                    F = B ^ C ^ D;
                    g = (3 * i + 5) % 16;
                } else {
                    F = C ^ (B | ~D);
                    g = (7 * i) % 16;
                }

                // The MD5 mixing function
                int temp = D;
                D = C;
                C = B;
                // Left rotate calculation
                int toRotate = A + F + K[i] + M[g];
                B = B + Integer.rotateLeft(toRotate, S[i]);
                A = temp;
            }

            // Add this chunk's hash to result so far
            a0 += A;
            b0 += B;
            c0 += C;
            d0 += D;
        }

        // 5. Output the 4 state variables as a 32-character Hex String (little-endian)
        return String.format("%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
                (byte) a0, (byte) (a0 >>> 8), (byte) (a0 >>> 16), (byte) (a0 >>> 24),
                (byte) b0, (byte) (b0 >>> 8), (byte) (b0 >>> 16), (byte) (b0 >>> 24),
                (byte) c0, (byte) (c0 >>> 8), (byte) (c0 >>> 16), (byte) (c0 >>> 24),
                (byte) d0, (byte) (d0 >>> 8), (byte) (d0 >>> 16), (byte) (d0 >>> 24));
    }
}

/*
 * HOW TO RUN THIS JAVA CODE:
 * 
 * 1. Open your terminal or command prompt.
 * 2. Navigate to the folder containing this file (e.g., cd IS).
 * 3. Compile the code using the command:
 *      javac assign7_scratch.java
 * 4. Run the compiled byte-code using the command:
 *      java assign7_scratch
 * 
 *
 * HOW THE MD5 ALGORITHM WORKS (THEORETICAL EXPLANATION):
 * 
 * MD5 processes data in blocks of 512 bits, breaking the message down mathematically to 
 * produce a fixed 128-bit (16-byte) hash value, represented as a 32-character Hexadecimal string.
 * 
 * 1. Append Padding Bits:
 *    The input message is padded so its length (in bits) is congruent to 448 modulo 512.
 *    Padding is always performed: a single "1" bit (0x80) is appended, followed by "0" bits.
 * 
 * 2. Append Length:
 *    A 64-bit representation of the original message length (before padding) is appended to 
 *    the end. This ensures the final padded message length is exactly a multiple of 512 bits.
 * 
 * 3. Initialize MD Buffer:
 *    A four-word buffer (A, B, C, D) is used to compute the message digest. These are 
 *    initialized to standard 32-bit magic numbers (e.g., A = 0x67452301).
 * 
 * 4. Process Message in 512-bit (64-byte) Blocks:
 *    The core of MD5 consists of 64 operations (grouped in 4 rounds of 16 operations).
 *    Each operation uses a non-linear function (F, G, H, or I), modular addition, and 
 *    left-rotations (using array S). It also incorporates a pseudo-random constant from 
 *    a precomputed table (array K based on the sine function) and a 32-bit chunk of the message.
 *    
 * 5. Output:
 *    After processing all 512-bit message blocks, the final state of registers A, B, C, and D 
 *    are concatenated sequentially. The integers are extracted in Little-Endian byte order 
 *    to construct the final 128-bit MD5 message digest.
 * 
 * 
 * IMPLEMENTATION DETAILS & CORE FORMULAS:
 * 
 * The 64 rounds of the hashing loop use 4 distinct non-linear bitwise functions (F, G, H, I):
 * 
 *    Round 1 (0 to 15):   F(B, C, D) = (B & C) | (~B & D)
 *    Round 2 (16 to 31):  G(B, C, D) = (B & D) | (C & ~D)
 *    Round 3 (32 to 47):  H(B, C, D) = B ^ C ^ D
 *    Round 4 (48 to 63):  I(B, C, D) = C ^ (B | ~D)
 * 
 * In each of the 64 iterations, the state variables are updated using the following formula:
 * 
 *    A = B + LeftRotate((A + Function(B, C, D) + M[g] + K[i]), shiftAmount)
 * 
 * Where:
 *  - 'Function' is one of F, G, H, or I depending on the round.
 *  - 'M[g]' is a 32-bit chunk of the message block.
 *  - 'K[i]' is a constant derived from the sine function: floor(2^32 * abs(sin(i + 1))).
 *  - 'LeftRotate' is a bitwise circular left shift operation.
 *  - After calculating A, we rotate the variables: A becomes D, D becomes C, C becomes B, B becomes A.
 */
