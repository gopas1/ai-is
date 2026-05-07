import java.security.MessageDigest;
import java.util.Scanner;

/*
 * MD5 ALGORITHM (Message Digest 5)
 * Theory: MD5 is a cryptographic hashing algorithm (NOT encryption).
 * Data is converted into a fixed-size 128-bit (16-byte) hash value.
 * Key properties of Hashing:
 * 1. One-Way: You can easily generate a hash from text, but you CANNOT reverse the hash back into text.
 * 2. Deterministic: "hello" will ALWAYS generate the exact same hash.
 * 3. Avalanche Effect: Changing just one character changes the entire hash completely.
 * Note: MD5 is now considered cryptographically broken because of "collisions" (two different files having the same hash), 
 * but it is still widely taught and used for basic file integrity checks (checksums).
 */

public class MD5Example {
    public static void main(String[] args) {
        // ANALYSIS NOTE: Using try-with-resources 'try (Scanner sc = new Scanner(System.in))' 
        // is preferred here to automatically close the stream and prevent memory leaks.
        try {
            Scanner sc = new Scanner(System.in);

            System.out.print("Enter text: ");
            String input = sc.nextLine();

            // STEP 1: Get an instance of the MD5 MessageDigest algorithm from Java's security library
            // ANALYSIS NOTE: .getInstance("MD5") throws a NoSuchAlgorithmException (a checked exception).
            // Java relies on "Providers" (like SUN or BouncyCastle). If the environment lacks an MD5 provider, it fails here.
            MessageDigest md = MessageDigest.getInstance("MD5");

            // STEP 2: Convert input string into an array of bytes, feed it to the algorithm, and compute the mathematical digest
            // CRITICAL ANALYSIS: input.getBytes() uses the platform's default charset (e.g., UTF-8 on Mac/Linux, but sometimes UTF-16/Windows-1252 on Windows).
            // To ensure the exact same hash across ALL operating systems globally, ALWAYS specify the encoding explicitly:
            // input.getBytes(java.nio.charset.StandardCharsets.UTF_8)
            byte[] messageDigest = md.digest(input.getBytes());

            // STEP 3: The result is an array of 16 bytes. 
            // We need to convert these raw bytes into a human-readable 32-character hexadecimal string.
            StringBuilder hexString = new StringBuilder();
            for (byte b : messageDigest) {
                // "%02x" formats each byte into exactly 2 lowercase hexadecimal characters.
                // PERFORMANCE ANALYSIS: String.format() internally compiles a regex-like pattern and handles localization,
                // making it quite slow inside a hot loop. 
                // For high-performance apps, bitwise operations are vastly superior:
                // hexString.append(Integer.toHexString((b >> 4) & 0xf)).append(Integer.toHexString(b & 0xf));
                hexString.append(String.format("%02x", b));
            }

            System.out.println("MD5 Message Digest: " + hexString.toString());

        } catch (Exception e) {
            // ANALYSIS NOTE: Catching generic 'Exception' is lazy practice. 
            // It's better to explicitly catch 'NoSuchAlgorithmException' to isolate cryptographic configuration errors.
            System.out.println("Error: " + e);
        }
    }
}
/* * ==========================================
 * MD5 ALGORITHM EXECUTION FLOW
 * ==========================================
 * 1. Read input string from the user.
 * 2. Initialize Java's built-in MD5 MessageDigest class.
 * 3. Convert the string into bytes and pass it to the `.digest()` function.
 * 4. Receive a 16-byte array as the hashed result.
 * 5. Loop through the 16 bytes. Convert each individual byte into a 2-character Hexadecimal format.
 * 6. Append them all together to form a final 32-character Hex String and print it.
 * * ==========================================
 * DRY RUN EXAMPLE
 * ==========================================
 * Input text: "hello"
 * * 1. Converts "hello" to bytes: [104, 101, 108, 108, 111]
 * 2. md.digest() processes these bytes through the complex MD5 padding and block operation math.
 * 3. Output is a 16-byte array buffer (values like [93, 65, 64, 42, ...])
 * 4. Hexadecimal conversion loop:
 * - byte 93 -> hex "5d"
 * - byte 65 -> hex "41"
 * - byte 64 -> hex "40"
 * - byte 42 -> hex "2a"
 * ... and so on for all 16 bytes.
 * 5. Final output concatenated: 
 * MD5 Message Digest: 5d41402abc4b2a76b9719d911017c592
 * * ==========================================
 * ADVANCED ARCHITECTURAL SECURITY METRICS (NOT PRESENT ABOVE)
 * ==========================================
 * 1. THE REASON MD5 IS BROKEN FOR PASSWORDS: 
 * MD5 is incredibly fast. A modern GPU can compute billions of MD5 hashes per second. 
 * This makes it completely vulnerable to "Brute-Force" and "Rainbow Table" (pre-computed hash database) attacks.
 * If an attacker steals an MD5 hash database, they can crack simple passwords almost instantly.
 * * 2. REPLACEMENTS FOR PRODUCTION CODE:
 * - For File Integrity Checksums: Use SHA-256 (via MessageDigest.getInstance("SHA-256")).
 * - For User Password Hashing: NEVER use MessageDigest. Use adaptive, intentionally slow algorithms 
 * that include built-in random "Salts" and multiple computational iterations (e.g., bcrypt, Argon2, or PBKDF2).
 * * 3. STATEFULNESS OF MessageDigest:
 * The `MessageDigest` object resets automatically after you call `.digest()`. 
 * This means you can reuse the same `md` instance to hash a new string right after without reinstantiating it.
 */