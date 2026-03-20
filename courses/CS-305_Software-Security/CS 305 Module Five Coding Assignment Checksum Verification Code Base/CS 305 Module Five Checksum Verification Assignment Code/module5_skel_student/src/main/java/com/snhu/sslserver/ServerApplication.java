package com.snhu.sslserver;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

@RestController
class ServerController {
    // Helper method to convert byte array to hex string
    private static String bytesToHex(byte[] hash) {
        StringBuilder hexString = new StringBuilder(2 * hash.length);
        for (byte b : hash) {
            String hex = Integer.toHexString(0xff & b);
            if (hex.length() == 1) hexString.append('0');
            hexString.append(hex);
        }
        return hexString.toString();
    }

    @RequestMapping("/hash")
    public String myHash() {
        String data = "Heath Davis";
        String checksumAlgorithm = "SHA-256";

        try {
            // Create MessageDigest instance for SHA-256
            MessageDigest md = MessageDigest.getInstance(checksumAlgorithm);

            // Add data string to digest
            md.update(data.getBytes());

            // Generate the hash value
            byte[] hashBytes = md.digest();

            // Convert to hex string
            String hashValue = bytesToHex(hashBytes);

            // Return formatted string with data and checksum
            return "<p>Data: " + data +
                    "<br>Name of Cipher Algorithm Used: " + checksumAlgorithm +
                    "<br>CheckSum Value: " + hashValue + "</p>";

        } catch (NoSuchAlgorithmException e) {
            return "<p>Error generating checksum: " + e.getMessage() + "</p>";
        }
    }
}