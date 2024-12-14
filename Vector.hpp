#pragma once

#include <cstddef>

namespace Vector {
struct IntVector {
    size_t size{};
    size_t capacity{};
    int* vector{};
};

struct CharVector {
    size_t size{};
    size_t capacity{};
    char* vector{};
};

struct KeysVector {
    size_t size{};
    bool createdSuccessfully{};
    int* vector{};
};

[[nodiscard]] IntVector CreateIntVector();
void DeleteVector(IntVector& vector);
void PushBack(IntVector& vector, int element);

[[nodiscard]] CharVector CreateCharVector();
void DeleteVector(CharVector& vector);
void PushBack(CharVector& vector, char element);

void DeleteVector(KeysVector& vector);
}  // namespace Vector
