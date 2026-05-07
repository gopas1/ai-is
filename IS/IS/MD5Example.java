import java.security.MessageDigest;
import java.util.Scanner;

public class MD5Example {
    public static void main(String[] args) {
        try {
            Scanner sc = new Scanner(System.in);

            System.out.print("Enter text: ");
            String input = sc.nextLine();

            // Create MD5 MessageDigest instance
            MessageDigest md = MessageDigest.getInstance("MD5");

            // Convert input string to bytes and compute digest
            byte[] messageDigest = md.digest(input.getBytes());

            // Convert byte array into hexadecimal format
            StringBuilder hexString = new StringBuilder();
            for (byte b : messageDigest) {
                hexString.append(String.format("%02x", b));
            }

            System.out.println("MD5 Message Digest: " + hexString.toString());

        } catch (Exception e) {
            System.out.println("Error: " + e);
        }
    }
}
/* 
PS C:\Users\com\Desktop\AI,IS\IS> javac MD5Example.java
PS C:\Users\com\Desktop\AI,IS\IS> java MD5Example
Enter text: hello
MD5 Message Digest: 5d41402abc4b2a76b9719d911017c592
*/