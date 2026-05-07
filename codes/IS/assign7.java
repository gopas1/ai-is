import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Scanner;

public class assign7 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("--- MD5 Message Digest Calculator ---");
        System.out.print("Enter the text to hash: ");
        String text = scanner.nextLine();

        try {
            // Initialize MessageDigest with the MD5 algorithm
            MessageDigest md = MessageDigest.getInstance("MD5");
            
            // Calculate the MD5 hash (returns an array of bytes)
            byte[] messageDigest = md.digest(text.getBytes());

            // Convert the byte array into a readable Hexadecimal string
            StringBuilder hexString = new StringBuilder();
            for (byte b : messageDigest) {
                String hex = Integer.toHexString(0xFF & b);
                if (hex.length() == 1) {
                    hexString.append('0'); // Pad with leading zero if needed
                }
                hexString.append(hex);
            }

            System.out.println("MD5 Hash (Message Digest): " + hexString.toString());

        } catch (NoSuchAlgorithmException e) {
            System.out.println("Error: MD5 algorithm not found in this Java environment.");
        }
        
        scanner.close();
    }
}

/*
 * HOW TO RUN THIS JAVA CODE:
 * 
 * 1. Open your terminal or command prompt.
 * 2. Navigate to the folder containing this file (e.g., cd IS).
 * 3. Compile the code using the command:
 *      javac assign7.java
 * 4. Run the compiled byte-code using the command:
 *      java assign7
 */
