package com.snhu.sslserver;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

@SpringBootApplication
public class ServerApplication {

    public static void main(String[] args) {
        SpringApplication.run(ServerApplication.class, args);
    }

}

@RestController
class ServerController {

    // Helper method to convert bytes to hex
    private String bytesToHex(byte[] bytes) {
        StringBuilder result = new StringBuilder();
        for (byte b : bytes) {
            result.append(String.format("%02x", b));
        }
        return result.toString();
    }

    @RequestMapping("/hash")
    public String myHash() throws NoSuchAlgorithmException {
        String data = "Hello Heath Davis!";

        // Create MessageDigest object with SHA-256
        MessageDigest md = MessageDigest.getInstance("SHA-256");

        // Generate hash
        byte[] hashBytes = md.digest(data.getBytes());
        String checksum = bytesToHex(hashBytes);

        return "<p>data: " + data +
                "<p>Name of Algorithm: SHA-256" +
                "<p>Checksum Value: " + checksum;
    }
}