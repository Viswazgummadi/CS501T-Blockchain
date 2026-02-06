#ifndef SHA256_UTILS_H
#define SHA256_UTILS_H

#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

// sha256 helper

inline std::string sha256(const std::string str) {
    // SHA256_DIGEST_LENGTH = 32 bytes by deafault

    unsigned char hash[SHA256_DIGEST_LENGTH];

    // create a context
    // init the context
    // update the context
    // final the context
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);

    // convert the hash(bytes) to a hex string
    //format the bytes to a hex string
    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    // return hex
    return ss.str();
}

#endif
