# Password Manager

A password manager written in C, focused on data structures, dynamic memory management, file I/O, and encryption.

The project was developed to explore low-level programming concepts while building a practical application for securely storing passwords.

## Features

- Master Password authentication
- Secure password storage
- Password encryption using **XChaCha20-Poly1305**
- Key derivation using **Argon2id**
- Random salt and nonce generation
- Encrypted binary vault (`vault.dat`)
- Hash Table and Linked List data structures
- Dynamic memory allocation
- File handling and serialization
- Authenticated decryption to detect incorrect passwords or corrupted data

## Technologies

- **Language:** C
- **Cryptography:** libsodium
- **Encryption:** XChaCha20-Poly1305
- **Key Derivation:** Argon2id
- **Data Structures:** Hash Tables, Linked Lists
- **Build System:** Make
- **CI/CD:** GitHub Actions

## Project Structure

```text
password-manager-v2/
│
├── src/
│   ├── main.c
│   ├── menu.c
│   ├── password.c
│   ├── linked_list.c
│   ├── hash_table.c
│   ├── storage.c
│   └── encryption.c
│
├── include/
│   ├── menu.h
│   ├── password.h
│   ├── linked_list.h
│   ├── hash_table.h
│   ├── storage.h
│   └── encryption.h
│
├── tests/
│   └── test_encryption.c
│
├── .github/
│   └── workflows/
│       └── windows.yml
│
├── Makefile
├── README.md
└── .gitignore
```

## How It Works

The application uses a Master Password to derive an encryption key through Argon2id.

The derived key is used with XChaCha20-Poly1305 to encrypt and authenticate the password vault.

The vault stores:

- Salt
- Nonce
- Encrypted data

The encryption key and Master Password are not stored in the vault.

When opening an existing vault, the application derives the key again and attempts authenticated decryption. An incorrect Master Password or modified vault causes authentication to fail.

## Building

### Requirements

- C compiler (GCC or Clang)
- libsodium
- Make

### Compile

```bash
make
```

### Run

```bash
./password-manager
```

## Windows

Windows builds are handled through GitHub Actions.

You can find the latest Windows executable in the repository's [Releases](https://github.com/chatz06/password-manager-v2/releases).

## Security

This project uses authenticated encryption and password-based key derivation through libsodium.

**Important:** This is an educational project and has not undergone an independent security audit. It should not yet be relied upon for storing real-world sensitive credentials.

## Learning Objectives

This project explores:

- Pointers and dynamic memory allocation in C
- Structures and modular programming
- Hash Tables and Linked Lists
- File I/O and binary file formats
- Data serialization and parsing
- Cryptography and secure key management
- Memory cleanup and error handling
- Cross-platform compilation and automated testing

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
