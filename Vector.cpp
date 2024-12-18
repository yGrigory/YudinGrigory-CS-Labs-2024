#include "Vector.hpp"

#include <iostream>

namespace {
const size_t kDefaultVectorCapacity = 8;
const size_t kGrowthFactor = 2;

void ResizeVector(Vector::IntVector& vector) {
    if (!vector.vector) {
        throw std::runtime_error("Некорректный вектор");
    }

    size_t newVectorSize = vector.capacity * kGrowthFactor;
    int* buffer = new int[newVectorSize];

    std::copy(vector.vector, vector.vector + vector.size, buffer);

    int* prevVector = vector.vector;
    vector.vector = buffer;

    vector.capacity = newVectorSize;

    delete[] prevVector;
}

void ResizeVector(Vector::CharVector& vector) {
    if (!vector.vector) {
        throw std::runtime_error("Некорректный вектор");
    }

    size_t newVectorSize = vector.capacity * kGrowthFactor;
    char* buffer = new char[newVectorSize];

    std::copy(vector.vector, vector.vector + vector.size, buffer);

    char* prevVector = vector.vector;
    vector.vector = buffer;

    vector.capacity = newVectorSize;

    delete[] prevVector;
}
}  // namespace

namespace Vector {
IntVector CreateIntVector() {
    int* array = new int[kDefaultVectorCapacity];

    return {.size = 0, .capacity = kDefaultVectorCapacity, .vector = array};
}

CharVector CreateCharVector() {
    char* array = new char[kDefaultVectorCapacity];

    return {.size = 0, .capacity = kDefaultVectorCapacity, .vector = array};
}

void DeleteVector(IntVector& vector) {
    vector.size = 0;
    vector.capacity = 0;

    delete[] vector.vector;

    vector.vector = nullptr;
}

void DeleteVector(CharVector& vector) {
    vector.size = 0;
    vector.capacity = 0;

    delete[] vector.vector;

    vector.vector = nullptr;
}

void DeleteVector(KeysVector& vector) {
    vector.size = 0;

    vector.isCreatedSuccessfully = false;

    delete[] vector.vector;

    vector.vector = nullptr;
}

void PushBack(IntVector& vector, int element) {
    if (!vector.vector) {
        throw std::runtime_error("Некорректный вектор");
    }

    if (vector.size >= vector.capacity) {
        ResizeVector(vector);
    }

    vector.vector[vector.size++] = element;
}

void PushBack(CharVector& vector, char element) {
    if (!vector.vector) {
        throw std::runtime_error("Некорректный вектор");
    }

    if (vector.size >= vector.capacity) {
        ResizeVector(vector);
    }

    vector.vector[vector.size++] = element;
}
}  // namespace Vector
