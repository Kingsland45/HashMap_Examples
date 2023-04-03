#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

/*
* compile using: g++ -o sha_256_hashCode sha_256_hashCode.cpp -lssl -lcrypto
* run using ./sha_256_hashCode
*/

unsigned long long generate_hashcode(const std::string& s) {
    // Encode the string to bytes using UTF-8 encoding
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (unsigned char c : s) {
        ss << std::setw(2) << static_cast<unsigned int>(c);
    }
    std::string encoded_s = ss.str();

    // Use SHA-256 hashing algorithm to generate a hash object
    unsigned char hash_bytes[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(encoded_s.c_str()), encoded_s.length(), hash_bytes);

    // Convert the hash bytes to an integer using big-endian byte order
    unsigned long long hash_int = 0;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        hash_int = (hash_int << 8) + hash_bytes[i];
    }

    // Return the hash integer
    return hash_int;
}

int main() {
    std::string s = "Hello, world!";
    unsigned long long hashcode = generate_hashcode(s);
    std::cout << "String: " << s << std::endl;
    std::cout << "Hash code: " << hashcode << std::endl;
    return 0;
}
