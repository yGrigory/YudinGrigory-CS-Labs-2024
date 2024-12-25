#include "Dictionary.hpp"

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

namespace {
const int kColumnSpace = 2;
const int kMaxWordLength = 1024;

const char* kFileName = "dictionary.txt";

void ResizeDictionary(Dictionary::Dictionary& dictionary, size_t newSize) {
    Dictionary::DictionaryField* buffer = new Dictionary::DictionaryField[newSize];

    std::copy(dictionary.fieldArray, dictionary.fieldArray + dictionary.size, buffer);

    Dictionary::DictionaryField* oldDict = dictionary.fieldArray;

    dictionary.fieldArray = buffer;
    dictionary.allocated_size = newSize;

    delete[] oldDict;
}

int CompareField(const Dictionary::DictionaryField& dictField, const Dictionary::DictionaryField& field) {
    if (!dictField.english && !dictField.russian) {
        return 0;
    }
    if (field.english) {
        return strcmp(dictField.english, field.english);
    }
    if (field.russian) {
        return strcmp(dictField.russian, field.russian);
    }
    return 0;
}

Dictionary::DictionaryField* BinaryLookUp(const Dictionary::Dictionary& dictionary, const Dictionary::DictionaryField& field) {
    size_t lowerBound = 0;
    size_t rightBound = dictionary.size - 1;

    while (rightBound - lowerBound > 1) {
        size_t idx = (lowerBound + rightBound) / 2;

        int comparisonResult = CompareField(dictionary.fieldArray[idx], field);

        if (comparisonResult < 0) {
            lowerBound = idx;
        } else if (comparisonResult == 0) {
            return &dictionary.fieldArray[idx];
        } else {
            rightBound = idx;
        }
    }

    return (CompareField(dictionary.fieldArray[lowerBound], field) >= 0) ? &dictionary.fieldArray[lowerBound] : &dictionary.fieldArray[rightBound];
}

Dictionary::DictionaryField* LookUp(const Dictionary::Dictionary& dictionary, const Dictionary::DictionaryField& field) {
    for (size_t i = 0; i < dictionary.size; i++) {
        if (CompareField(dictionary.fieldArray[i], field) == 0) {
            return &dictionary.fieldArray[i];
        }
    }

    return nullptr;
}

bool FieldExists(const Dictionary::Dictionary& dictionary, const Dictionary::DictionaryField& field) {
    Dictionary::DictionaryField* wordPtr = BinaryLookUp(dictionary, field);

    if (!wordPtr) {
        return false;
    }

    return wordPtr->english && wordPtr->russian && (CompareField(*wordPtr, field) == 0);
}

namespace Dictionary {
Dictionary CreateDictionary() {
    return Dictionary{.fieldArray = new DictionaryField[]{{nullptr, nullptr}}, .allocated_size = 1, .size = 0, .maxWordLength = 0};
}

DictionaryField* AddWord(Dictionary& dictionary, const DictionaryField& field) {
    if (dictionary.size > 0 && FieldExists(dictionary, field)) {
        return nullptr;
    }

    if (dictionary.size >= dictionary.allocated_size) {
        ResizeDictionary(dictionary, dictionary.size + 1);
        dictionary.fieldArray[dictionary.size] = {nullptr, nullptr};
    }

    dictionary.size++;

    DictionaryField* wordPtr = BinaryLookUp(dictionary, field);

    if (!wordPtr) {
        return nullptr;
    }

    if (wordPtr->english && wordPtr->russian && CompareField(*wordPtr, field) == 0) {
        return nullptr;
    }

    std::move(wordPtr, dictionary.fieldArray + dictionary.size - 1, wordPtr + 1);
    *wordPtr = field;

    dictionary.maxWordLength = std::max(dictionary.maxWordLength, static_cast<int>(std::max(strlen(field.english), strlen(field.russian))));

    return wordPtr;
}
void DeleteWord(Dictionary& dictionary, size_t idx) {
    DeleteField(dictionary.fieldArray[idx]);

    std::move(dictionary.fieldArray + idx + 1, dictionary.fieldArray + dictionary.size--, dictionary.fieldArray + idx);
}

const char* TranslationIntoRussian(const Dictionary& dictionary, const char* word) {
    DictionaryField* wordPtr = BinaryLookUp(dictionary, {.english = word, .russian = nullptr});

    if (!wordPtr || std::strcmp(wordPtr->english, word) != 0) {
        return nullptr;
    }

    return wordPtr->russian;
}
const char* TranslationIntoEnglish(const Dictionary& dictionary, const char* word) {
    DictionaryField* wordPtr = LookUp(dictionary, {.english = nullptr, .russian = word});

    if (!wordPtr) {
        return nullptr;
    }

    return wordPtr->english;
}

void PrintDictionary(const Dictionary& dictionary) {
    std::cout << std::endl;
    std::cout << std::left << std::setw(kColumnSpace) << "N";
    std::cout << std::setw(dictionary.maxWordLength * 2) << "English";
    std::cout << std::setw(dictionary.maxWordLength * 2) << "Russian" << std::endl;

    for (size_t i = 0; i < dictionary.size; ++i) {
        std::cout << std::setw(kColumnSpace) << i;
        std::cout << std::setw(dictionary.maxWordLength * 2) << dictionary.fieldArray[i].english;
        std::cout << std::setw(dictionary.maxWordLength * 2) << dictionary.fieldArray[i].russian << std::endl;
    }

    std::cout << std::endl;
}

Dictionary MakeFromFile() {
    std::ifstream file(kFileName);

    Dictionary dictionary = CreateDictionary();

    if (file.is_open()) {
        while (!file.eof()) {
            char* bufferEnglish = new char[kMaxWordLength];
            char* bufferRussian = new char[kMaxWordLength];

            file.getline(bufferEnglish, kMaxWordLength);
            file.getline(bufferRussian, kMaxWordLength);

            if (file.eof()) {
                break;
            }

            DictionaryField field{bufferEnglish, bufferRussian};

            AddWord(dictionary, field);
        }

        file.close();
    }

    return dictionary;
}

void SaveDictionaryIntoFile(const Dictionary& dictionary) {
    std::ofstream file(kFileName);

    if (file.is_open()) {
        for (size_t i = 0; i < dictionary.size; ++i) {
            file << dictionary.fieldArray[i].english << std::endl << dictionary.fieldArray[i].russian << std::endl;
        }

        file.close();
    }
}

void DeleteDictionary(Dictionary& dictionary) {
    dictionary.size = 0;
    dictionary.allocated_size = 0;

    for (size_t i = 0; i < dictionary.size; i++) {
        DeleteField(dictionary.fieldArray[i]);
    }

    delete[] dictionary.fieldArray;
}

void DeleteField(DictionaryField& field) {
    delete[] field.english;
    delete[] field.russian;
}
}  // namespace Dictionary
