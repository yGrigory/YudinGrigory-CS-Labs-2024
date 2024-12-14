#include "Vector.hpp"

#include <iostream>

namespace {
const size_t kDefaultVectorCapacity = 8;
const size_t kGrowthFactor = 2;

void ResizeVector(Vector::IntVector& vector) {
    if (!vector.vector) {
        throw std::runtime_error("invalid vector");
    }

    size_t newVectorSize = vector.capacity * kGrowthFactor;
    int* buffer = new int[newVectorSize];

    std::copy(vector.vector, vector.vector + vector.size, buffer);

    int* oldVector = vector.vector;
    vector.vector = buffer;

    vector.capacity = newVectorSize;

    delete[] oldVector;
}

void ResizeVector(Vector::CharVector& vector) {
    if (!vector.vector) {
        throw std::runtime_error("invalid vector");
    }

    size_t newVectorSize = vector.capacity * kGrowthFactor;
    char* buffer = new char[newVectorSize];

    std::copy(vector.vector, vector.vector + vector.size, buffer);

    char* oldVector = vector.vector;
    vector.vector = buffer;

    vector.capacity = newVectorSize;

    delete[] oldVector;
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

    vector.createdSuccessfully = false;

    delete[] vector.vector;

    vector.vector = nullptr;
}

void PushBack(IntVector& vector, int element) {
    if (!vector.vector) {
        throw std::runtime_error("invalid vector");
    }

    if (vector.size >= vector.capacity) {
        ResizeVector(vector);
    }

    vector.vector[vector.size++] = element;
}

void PushBack(CharVector& vector, char element) {
    if (!vector.vector) {
        throw std::runtime_error("invalid vector");
    }

    if (vector.size >= vector.capacity) {
        ResizeVector(vector);
    }

    vector.vector[vector.size++] = element;
}
}  // namespace Vector
