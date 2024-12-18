#pragma once

#include "Vector.hpp"

namespace Encryption {
const int kCharactesNumber = 128;

struct Character {
    int encountersNumber{};
    int encryptionOptionsNumber{};
    bool encryptionOptions[kCharactesNumber]{};
};

void StartApp(int argc, char** argv);

[[nodiscard]] Vector::KeysVector CreateKeysArray(const char* keysFile);

void EncryptFile(const char* sourceFile, const char* destinationFile, const Vector::KeysVector& keysVector,
                 Encryption::Character* characterStatistics);
void DecryptFile(const char* sourceFile, const char* destinationFile, const Vector::KeysVector& keysVector);

void PrintStatistics(const Vector::KeysVector& keysVector, const Encryption::Character* characterStatistics, size_t size);
}  // namespace Encryption
