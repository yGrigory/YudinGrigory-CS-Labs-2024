#include "Encryption.hpp"

#include "Vector.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>

namespace {
const int kRequiredArgsNumber = 5;
const int kSourceFileIndex = 1;
const int kKeysFileIndex = 2;
const int kEncryptedFileIndex = 3;
const int kDecryptedFileIndex = 4;

const int kBufferSize = 1024;

const int kMaxWordLength = 20;

void ReadFile(const char* filename, Vector::CharVector& destination) {
    if (!filename || !destination.vector) {
        return;
    }

    std::ifstream fin{};
    fin.open(filename, std::ios::binary);

    if (!fin.is_open() || !destination.vector) {
        return;
    }

    char buffer[kBufferSize]{};

    while (!fin.eof()) {
        fin.read(buffer, kBufferSize);
        size_t readCharactersNumber = fin.gcount();

        for (size_t i = 0; i < readCharactersNumber; ++i) {
            Vector::PushBack(destination, buffer[i]);
        }
    }

    fin.close();
}

void WriteFile(const char* filename, const Vector::CharVector& content) {
    if (!filename || !content.vector) {
        return;
    }

    std::ofstream fout{};
    fout.open(filename, std::ios::binary | std::ios::out);

    if (!fout.is_open()) {
        return;
    }

    fout.write(content.vector, static_cast<int>(content.size));

    fout.close();
}

void Encrypt(const Vector::CharVector& source, Vector::CharVector& destination, const Vector::KeysVector& keysVector,
             Encryption::Character* characterStatistics) {
    if (!source.vector || !destination.vector || !keysVector.createdSuccessfully || !keysVector.vector) {
        return;
    }

    for (size_t i = 0; i < source.size; ++i) {
        int characterCode = static_cast<int>(source.vector[i]);
        int encryptedCharacterCode = (characterCode + keysVector.vector[i % keysVector.size]) % Encryption::kCharactesNumber;

        Vector::PushBack(destination, static_cast<char>(encryptedCharacterCode));

        if (characterStatistics) {
            ++characterStatistics[characterCode].encountersNumber;

            if (!characterStatistics[characterCode].encryptionOptions[encryptedCharacterCode]) {
                characterStatistics[characterCode].encryptionOptions[encryptedCharacterCode] = true;
                ++characterStatistics[characterCode].encryptionOptionsNumber;
            }
        }
    }
}

void Decrypt(const Vector::CharVector& source, Vector::CharVector& destination, const Vector::KeysVector& keysVector) {
    if (!source.vector || !destination.vector || !keysVector.createdSuccessfully || !keysVector.vector) {
        return;
    }

    for (size_t i = 0; i < source.size; ++i) {
        int decryptedCharacterCode = static_cast<int>(source.vector[i]) - keysVector.vector[i % keysVector.size];

        if (decryptedCharacterCode < 0) {
            decryptedCharacterCode = Encryption::kCharactesNumber - (-decryptedCharacterCode % Encryption::kCharactesNumber);
        }

        Vector::PushBack(destination, static_cast<char>(decryptedCharacterCode));
    }
}

void GetEncounteredCharacters(const Encryption::Character* characterStatistics, size_t size, Vector::IntVector& destination) {
    if (!characterStatistics || !destination.vector) {
        return;
    }

    for (size_t i = 0; i < size; ++i) {
        if (characterStatistics[i].encountersNumber > 0) {
            Vector::PushBack(destination, static_cast<int>(i));
        }
    }
}

void PrintTableRows(const Encryption::Character* characterStatistics, const Vector::IntVector& encounteredCharacters, size_t startIndex,
                    size_t endIndex) {
    if (!characterStatistics || !encounteredCharacters.vector) {
        return;
    }

    const int threeCharWidth = 3;
    const int fiveCharWidth = 5;

    if (startIndex >= 0 && startIndex < encounteredCharacters.size) {
        std::cout << "\n Символ | Код в таблице ASCII | Сколько раз встретился в тексте | Количество различных шифрований ";
        std::cout << "\n--------------------------------------------------------------------------------------------------\n";
    }

    for (size_t i = startIndex; i < std::min(encounteredCharacters.size, endIndex); ++i) {
        int characterCode = encounteredCharacters.vector[i];

        if (static_cast<char>(characterCode) == '\n') {
            std::cout << "   " << '\\' << "n   ";
        } else {
            std::cout << "    " << static_cast<char>(characterCode) << "   ";
        }

        std::cout << "|         " << std::setw(threeCharWidth) << characterCode << "         |              " << std::setw(fiveCharWidth)
                  << characterStatistics[characterCode].encountersNumber << "              |              " << std::setw(fiveCharWidth)
                  << characterStatistics[characterCode].encryptionOptionsNumber;
        std::cout << "\n--------------------------------------------------------------------------------------------------\n";
    }

    std::cout << '\n';
}






void PrintStatisticsTable(const Encryption::Character* characterStatistics, size_t size) {
    if (!characterStatistics) {
        return;
    }

    const int rowsNumber = 5;
    Vector::IntVector encounteredCharacters = Vector::CreateIntVector();
    GetEncounteredCharacters(characterStatistics, size, encounteredCharacters);
    size_t startIndex{};
    size_t endIndex = rowsNumber;
    char answer = 'd';

    while (answer != 'f' && (endIndex - rowsNumber) <= encounteredCharacters.size) {
        if (startIndex >= 0 && (answer == 'd' || answer == 'u')) {
            PrintTableRows(characterStatistics, encounteredCharacters, startIndex, endIndex);
        }
        std::cout << "Введите символ d, чтобы продолжить вывести следующие строки, символ u, чтобы вывести предыдущие строки, символ f, чтобы "
                     "закончить вывод таблицы\n";
        std::cin >> answer;
        if (answer == 'd' && endIndex < encounteredCharacters.size) {
            startIndex += rowsNumber;
            endIndex += rowsNumber;
        } else if (answer == 'u' && startIndex > 0) {
            startIndex -= rowsNumber;
            endIndex -= rowsNumber;
        } else if (answer != 'd' && answer != 'u' && answer != 'f') {
            std::cout << "Введены некорректные данные\n";
        }
    }

    Vector::DeleteVector(encounteredCharacters);
}

void PrintCharacterStatistics(const Encryption::Character* characterStatistics, size_t size) {
    if (!characterStatistics) {
        return;
    }
    const int threeCharWidth = 3;
    const int fiveCharWidth = 5;
    char answer{};
    char character{};
    int characterCode{};
    while (answer != 'f') {
        std::cout << "Введите символ c, чтобы вывести статику по символу, символ n, чтобы вывести статистику по коду символа, символ f, чтобы не "
                     "выводить статистику\n";
        std::cin >> answer;
        if (answer != 'c' && answer != 'n' && answer != 'f') {
            std::cout << "Введены некорректные данные\n";
        } else if (answer != 'f') {
            if (answer == 'c') {
                std::cout << "Введите символ, статистику которого вы хотите вывести\n";
                std::cin.clear();
                std::cin.ignore();
                std::cin.get(character);
                characterCode = static_cast<int>(character);
            } else {
                std::cout << "Введите код символа, статистику которого вы хотите вывести\n";
                std::cin >> characterCode;
            }
            if (characterCode < 0 || static_cast<size_t>(characterCode) >= size) {
                std::cout << "Символ не встречался в исходном тексте\n";
            } else if (!characterStatistics[characterCode].encountersNumber) {
                std::cout << "Символ не встречался в исходном тексте\n";
            } else {
                std::cout << "\n Символ | Код в таблице ASCII | Сколько раз встретился в тексте | Количество различных шифрований ";
                std::cout << "\n--------------------------------------------------------------------------------------------------\n";
                if (static_cast<char>(characterCode) == '\n') {
                    std::cout << "   " << '\\' << "n   ";
                } else {
                    std::cout << "    " << static_cast<char>(characterCode) << "   ";
                }
                std::cout << "|         " << std::setw(threeCharWidth) << characterCode << "         |              " << std::setw(fiveCharWidth)
                          << characterStatistics[characterCode].encountersNumber << "              |              " << std::setw(fiveCharWidth)
                          << characterStatistics[characterCode].encryptionOptionsNumber;
                std::cout << "\n--------------------------------------------------------------------------------------------------\n";
            }
            std::cout << '\n';
        }
    }
}
}  // namespace
namespace Encryption {

void PrintStatistics(const Vector::KeysVector& keysVector, const Encryption::Character* characterStatistics, size_t size) {
    if (!characterStatistics || !keysVector.createdSuccessfully || !keysVector.vector) {
        return;
    }

    std::cout << "\nКоличество слов в кодовом блокноте: " << keysVector.size << '\n';

    int sourceTextLength{};
    for (size_t i = 0; i < size; ++i) {
        sourceTextLength += characterStatistics[i].encountersNumber;
    }

    std::cout << "Количество символов в исходном тексте: " << sourceTextLength << "\n\n";

    char answer{};
    while (answer != 'e') {
        std::cout << "Введите символ t, чтобы вывести таблицу статистики символов исходного текста, символ c, чтобы вывести статистку о конкретном "
                     "символе, символ e, чтобы завершить вывод статистики\n";
        std::cin >> answer;

        if (answer != 't' && answer != 'c' && answer != 'e') {
            std::cout << "Введены некорректные данные\n";
        } else if (answer == 't') {
            PrintStatisticsTable(characterStatistics, size);
        } else if (answer == 'c') {
            PrintCharacterStatistics(characterStatistics, size);
        }
    }
}

Vector::KeysVector CreateKeysArray(const char* keysFilename) {
    if (!keysFilename) {
        return {.createdSuccessfully = false};
    }

    Vector::CharVector keysFileContent = Vector::CreateCharVector();
    ReadFile(keysFilename, keysFileContent);

    Vector::IntVector keysVector = Vector::CreateIntVector();

    bool wordEnded = false;

    int wordLength{};
    int wordCode{};

    for (size_t i = 0; i < keysFileContent.size; ++i) {
        char character = keysFileContent.vector[i];

        if (character == ' ' || character == '\n' || std::ispunct(character)) {
            wordEnded = true;
        } else {
            ++wordLength;
            wordCode += static_cast<int>(keysFileContent.vector[i]);
        }

        if (wordEnded || wordLength == kMaxWordLength) {
            if (wordLength > 0) {
                Vector::PushBack(keysVector, wordCode);
                wordLength = 0;
                wordCode = 0;
            }

            wordEnded = false;
        }
    }

    Vector::DeleteVector(keysFileContent);

    return {.size = keysVector.size, .createdSuccessfully = true, .vector = keysVector.vector};
}













void EncryptFile(const char* sourceFilename, const char* destinationFilename, const Vector::KeysVector& keysVector,
                 Encryption::Character* characterStatistics) {
    if (!sourceFilename || !destinationFilename || !keysVector.vector) {
        return;
    }

    Vector::CharVector sourceFileContent = Vector::CreateCharVector();
    ReadFile(sourceFilename, sourceFileContent);

    Vector::CharVector encryptedSourceFileContent = Vector::CreateCharVector();
    Encrypt(sourceFileContent, encryptedSourceFileContent, keysVector, characterStatistics);

    WriteFile(destinationFilename, encryptedSourceFileContent);

    Vector::DeleteVector(sourceFileContent);
    Vector::DeleteVector(encryptedSourceFileContent);
}

void DecryptFile(const char* sourceFilename, const char* destinationFilename, const Vector::KeysVector& keysVector) {
    if (!sourceFilename || !destinationFilename || !keysVector.vector || !keysVector.createdSuccessfully) {
        return;
    }

    Vector::CharVector encryptedSourceFileContent = Vector::CreateCharVector();
    ReadFile(sourceFilename, encryptedSourceFileContent);

    Vector::CharVector decryptedSourceFileContent = Vector::CreateCharVector();
    Decrypt(encryptedSourceFileContent, decryptedSourceFileContent, keysVector);

    WriteFile(destinationFilename, decryptedSourceFileContent);

    Vector::DeleteVector(encryptedSourceFileContent);
    Vector::DeleteVector(decryptedSourceFileContent);
}

void StartApp(int argc, char** argv) {
    if (!argv) {
        return;
    }

    if (argc < kRequiredArgsNumber) {
        std::cout << "Введено недостаточное количество данных";
        return;
    }

    char* sourceFileName = argv[kSourceFileIndex];
    char* keysFilename = argv[kKeysFileIndex];
    char* encryptedFileName = argv[kEncryptedFileIndex];
    char* decryptedFileName = argv[kDecryptedFileIndex];

    Vector::KeysVector keysVector = CreateKeysArray(keysFilename);

    if (!keysVector.createdSuccessfully) {
        std::cout << "Не удалось определить ключи шифрования";
        return;
    }

    Character characterStatistics[kCharactesNumber]{};

    EncryptFile(sourceFileName, encryptedFileName, keysVector, characterStatistics);
    DecryptFile(encryptedFileName, decryptedFileName, keysVector);

    PrintStatistics(keysVector, characterStatistics, kCharactesNumber);

    Vector::DeleteVector(keysVector);
}
}  // namespace Encryption
