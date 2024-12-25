#pragma once

#include <cstddef>

namespace Dictionary {

struct DictionaryField {
    const char* english;
    const char* russian;
};

struct Dictionary {
    DictionaryField* fieldArray;

    size_t allocated_size;
    size_t size;

    int maxWordLength;
};

Dictionary CreateDictionary();

DictionaryField* AddWord(Dictionary& dictionary, const DictionaryField& word);
void DeleteWord(Dictionary& dictionary, size_t idx);

[[nodiscard]] const char* TranslationIntoRussian(const Dictionary& dictionary, const char* word);
[[nodiscard]] const char* TranslationIntoEnglish(const Dictionary& dictionary, const char* word);

void PrintDictionary(const Dictionary& dictionary);

[[nodiscard]] Dictionary MakeFromFile();
void SaveDictionaryIntoFile(const Dictionary& dictionary);

void DeleteDictionary(Dictionary& dictionary);
void DeleteField(DictionaryField& field);
}  // namespace Dictionary
