# CS-305: Software Security

## Course Overview

CS-305 is a comprehensive course in software security offered by Southern New Hampshire University (SNHU). This course covers the fundamental principles and practices of developing secure software applications, with a focus on real-world implementation of security best practices in modern web applications and REST APIs.

## Course Description

This course provides students with practical knowledge and hands-on experience in implementing security measures throughout the software development lifecycle. Students learn how to identify and mitigate common security vulnerabilities, implement cryptographic solutions, and design secure authentication and authorization mechanisms. The course emphasizes secure coding practices and demonstrates how to build resilient applications that protect against exploitation.

## Topics Covered

- **Secure Coding Practices**
  - Secure input validation
  - Output encoding and sanitization
  - Error handling and logging best practices
  - Defense against common vulnerabilities

- **Cryptography & Checksums**
  - Hash algorithms (SHA-256, SHA-512)
  - Message digest computation and verification
  - Checksum validation for data integrity
  - Cryptographic algorithms and their applications

- **SSL/TLS & HTTPS**
  - Secure Socket Layer (SSL) protocol implementation
  - Transport Layer Security (TLS) configuration
  - Certificate management and keystores
  - HTTPS server setup with Spring Boot

- **Authentication & Authorization**
  - Basic authentication mechanisms
  - User authentication implementation
  - Role-based authorization (RBAC)
  - Game authentication and user management systems

- **Dependency Vulnerability Management**
  - OWASP Dependency Check tool
  - Identifying vulnerable dependencies
  - Scanning projects for known vulnerabilities
  - Keeping libraries and frameworks up-to-date

- **Web Application Security**
  - REST API security
  - CRUD operations with security considerations
  - Health check endpoints
  - Client-server communication security

- **OWASP Standards**
  - OWASP Top 10 vulnerabilities
  - Secure development guidelines
  - Vulnerability assessment and remediation

## Languages & Tools

### Languages
- **Java 8+** - Primary programming language
- **Spring Boot** - Web framework and REST API development
- **Maven** - Build and dependency management

### Frameworks & Libraries
- **Spring Boot 2.2.4** - Web application framework
- **Spring Data REST** - RESTful web service development
- **Dropwizard 2.0.18** - Lightweight Java framework for microservices
- **Bouncy Castle** - Cryptography provider (bcprov-jdk15on)
- **Jackson** - JSON processing library

### Tools & Plugins
- **OWASP Dependency Check Maven Plugin** - Vulnerability scanning
- **Maven Wrapper** - Consistent Maven builds
- **Eclipse/IntelliJ IDE** - Development environments

## Projects & Assignments

### Project One: REST Service with CRUD Operations
- **Location:** `CS 305 Project One Code Base/rest-service`
- **Focus:** Building a RESTful web service with secure data handling
- **Components:**
  - CRUD data model and controller
  - REST endpoints for data management
  - Customer and document data handling
  - Secure Spring Boot application

### Project Two: SSL/TLS Server Implementation
- **Location:** `CS 305 Project Two Code Base/ssl-server_student`
- **Focus:** Implementing secure HTTPS communication
- **Components:**
  - SSL/TLS configuration in Spring Boot
  - Secure server setup
  - Certificate and keystore management
  - HTTPS endpoint implementation

### Module Two: Secure Coding & Data Handling
- **Location:** `CS 305 Module Two Written Assignment Code Base (1)/Module2.1`
- **Focus:** Fundamentals of secure coding practices
- **Topics:**
  - Secure application design
  - Input validation
  - Data protection mechanisms

### Module Five: Checksum Verification Assignment
- **Location:** `CS 305 Module Five Coding Assignment Checksum Verification Code Base`
- **Focus:** Implementing data integrity verification using cryptographic checksums
- **Components:**
  - SHA-256 hash computation
  - MessageDigest implementation
  - Checksum return endpoints
  - Hex string conversion utilities
  - Keystore and SSL configuration

### Module Six: Advanced Security Topics
- **Location:** `CS 305 Module Six Code Base 6-25`
- **Focus:** Advanced REST service security
- **Components:**
  - Secured REST endpoints
  - Advanced Spring Boot configuration

### GameAuth Authentication System
- **Location:** `gameauth/gameauth/gameauth/FIXME/gameauth`
- **Framework:** Dropwizard (alternative to Spring Boot)
- **Focus:** Authentication and authorization in web applications
- **Components:**
  - GameAuthenticator - Basic authentication implementation
  - GameAuthorizer - Role-based authorization
  - GameUserDB - User database management
  - REST controllers for user management
  - Health check endpoints
  - Configuration management

## Key Concepts

### Secure Coding
- Writing code resistant to common attacks (injection, XSS, CSRF)
- Proper exception handling without exposing sensitive information
- Secure logging practices without storing sensitive data

### Cryptography
- Understanding cryptographic algorithms and their properties
- Message digest computation for data integrity
- Hash-based verification mechanisms
- Secure key management and storage

### Web Application Security
- Securing REST APIs and web services
- Implementing proper authentication and authorization
- Secure communication using TLS/SSL
- Protecting against common web vulnerabilities

### Dependency Management
- Using OWASP Dependency Check to identify vulnerable libraries
- Keeping dependencies current and patched
- Understanding transitive dependency risks

### Secure Architecture
- Building layered security into applications
- Separating concerns (authentication, authorization, business logic)
- Defense in depth strategies

## File Index

### Directory Structure

```
CS-305_Software-Security/
├── README.md (this file)
├── CS 305 Project One Code Base/
│   └── rest-service/                    # Spring Boot REST API project
│       ├── pom.xml                      # Maven configuration with OWASP Dependency Check
│       ├── src/main/java/com/twk/restservice/
│       │   ├── RestServiceApplication.java
│       │   ├── CRUDController.java
│       │   ├── CRUD.java
│       │   ├── GreetingController.java
│       │   ├── Greeting.java
│       │   ├── customer.java
│       │   ├── myDateTime.java
│       │   └── DocData.java
│       └── src/test/java/                # Unit tests
├── CS 305 Project Two Code Base/
│   └── ssl-server_student/              # SSL/TLS server implementation
│       ├── pom.xml
│       ├── src/main/resources/
│       │   └── keystore.p12             # SSL certificate and key storage
│       └── src/main/java/com/snhu/sslserver/
│           └── SslServerApplication.java
├── CS 305 Module Two Written Assignment Code Base (1)/
│   └── Module2.1/                       # Secure coding fundamentals
│       ├── pom.xml
│       └── src/main/java/com/snhu/Module21/
├── CS 305 Module Five Coding Assignment Checksum Verification Code Base/
│   └── module5_skel_student/            # Checksum verification assignment
│       ├── pom.xml
│       ├── src/main/resources/
│       │   ├── keystore
│       │   └── keystore.p12
│       ├── src/main/java/com/snhu/sslserver/
│       │   └── ServerApplication.java   # Hash/checksum implementation
│       └── src/test/java/
├── CS 305 Module Six Code Base 6-25/
│   └── rest-service/                    # Advanced REST security
│       ├── pom.xml
│       └── src/main/java/com/snhu/restservice/
└── gameauth/
    └── gameauth/gameauth/FIXME/gameauth/  # Dropwizard authentication system
        ├── pom.xml
        ├── config.yml
        ├── src/main/java/com/gamingroom/gameauth/
        │   ├── GameAuthApplication.java
        │   ├── GameAuthConfiguration.java
        │   ├── auth/
        │   │   ├── GameAuthenticator.java
        │   │   ├── GameAuthorizer.java
        │   │   └── GameUser.java
        │   ├── controller/
        │   │   ├── GameUserRESTController.java
        │   │   └── RESTClientController.java
        │   ├── dao/
        │   │   └── GameUserDB.java
        │   ├── healthcheck/
        │   │   ├── AppHealthCheck.java
        │   │   └── HealthCheckController.java
        │   └── representations/
        │       └── GameUserInfo.java
        └── src/main/resources/
            └── banner.txt
```

### Key Files Reference

| File | Purpose |
|------|---------|
| `pom.xml` | Maven project configuration, dependency management, OWASP plugin setup |
| `RestServiceApplication.java` | Entry point for REST service applications |
| `SslServerApplication.java` | Secure HTTPS server implementation |
| `GameAuthApplication.java` | Authentication service entry point |
| `GameAuthenticator.java` | Basic authentication implementation with role-based access |
| `ServerApplication.java` (Module 5) | SHA-256 checksum computation and verification |
| `keystore.p12` | SSL/TLS certificates and private keys |
| `CRUDController.java` | REST controller for Create, Read, Update, Delete operations |
| `application.properties` | Spring Boot configuration files |
| `config.yml` | Dropwizard application configuration |

## Semester & Year

This course material appears to be from the **2019-2020 academic year** based on file dates and Spring Boot 2.2.4.RELEASE version (released March 2020).

## Learning Outcomes

Upon completion of CS-305, students will be able to:

1. **Identify** security vulnerabilities in source code
2. **Implement** secure coding practices using industry-standard frameworks
3. **Configure** SSL/TLS for secure communication
4. **Design** authentication and authorization systems
5. **Develop** cryptographic solutions for data integrity
6. **Analyze** dependencies for security vulnerabilities
7. **Apply** OWASP guidelines to web application development
8. **Test** security implementations effectively

## Course Structure

The course is organized into 8 modules:

- **Module 1:** Introduction to Software Security
- **Module 2:** Secure Coding Fundamentals (Written & Coding Assignments)
- **Module 3:** Security Tools and Techniques
- **Module 4:** REST API Security
- **Module 5:** Cryptography and Checksums (Coding Assignment)
- **Module 6:** Advanced Security Topics
- **Module 7:** Vulnerability Assessment
- **Module 8:** Final Project & Capstone

## Technologies Summary

| Technology | Version | Purpose |
|-----------|---------|---------|
| Java | 8 | Programming Language |
| Spring Boot | 2.2.4.RELEASE | Web Framework |
| Maven | Latest | Build Tool |
| Dropwizard | 2.0.18 | Lightweight Framework (GameAuth) |
| Bouncy Castle | 1.46 | Cryptography Provider |
| Jackson | Latest | JSON Processing |

## Getting Started

### Prerequisites
- Java Development Kit (JDK) 8 or higher
- Maven 3.6+
- Git
- IDE (Eclipse or IntelliJ IDEA recommended)

### Building a Project
```bash
cd "CS 305 Project One Code Base/rest-service"
mvn clean install
mvn spring-boot:run
```

### Running Dependency Checks
```bash
mvn dependency-check:check
```

### Testing
```bash
mvn test
```

## Resources & References

- [OWASP Top 10](https://owasp.org/www-project-top-ten/)
- [Spring Boot Documentation](https://spring.io/projects/spring-boot)
- [OWASP Dependency Check](https://owasp.org/www-project-dependency-check/)
- [Java Cryptography Architecture (JCA)](https://docs.oracle.com/javase/8/docs/technotes/guides/security/crypto/CryptoSpec.html)
- [SNHU CS-305 Course Materials](https://snhu.edu)

## Notes

- Projects include skeleton code (marked with FIXME comments) for students to complete
- Multiple versions of assignments exist showing iterative development
- Both Spring Boot and Dropwizard frameworks are covered for different architectural approaches
- Emphasis on practical, production-ready security implementations

---

*This README was generated to provide a comprehensive overview of the CS-305 Software Security course materials and projects.*
