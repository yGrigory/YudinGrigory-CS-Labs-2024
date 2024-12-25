#include "Logic.hpp"

#include "Dictionary.hpp"

#include <iostream>

namespace {
const int kMaxWordLength = 1024;

void ClearCin() {
    char a[1];
    std::cin.getline(a, 1);
}

char* InputEnglishWord() {
    char* word = new char[kMaxWordLength];
    std::cout << "Введите слово на английском: ";
    std::cin.getline(word, kMaxWordLength);
    return word;
}

char* InputRussianWord() {
    char* word = new char[kMaxWordLength];
    std::cout << "Введите слово на русском: ";
    std::cin.getline(word, kMaxWordLength);
    return word;
}
}  // namespace

namespace Menu {
    int RunTask(Dictionary::Dictionary & dictionary, Task task) {
        switch (task) {
            case Task::AddWord: {
                std::cout << std::endl;

                if (!Dictionary::AddWord(dictionary, {InputEnglishWord(), InputRussianWord()})) {
                    std::cout << "Такое слово уже существует!" << std::endl;

                } else {
                    std::cout << "Слово успешно добавлено!" << std::endl << std::endl;
                }
                break;
            }
            case Task::DeleteWord: {
                std::cout << std::endl;
                size_t index{};

                std::cout << "Введите индекс слова: ";
                std::cin >> index;
                ClearCin();

                Dictionary::DeleteWord(dictionary, index);
                std::cout << "Слово успешно удалено.\n\n";
                break;
            }
            case Task::TranslationIntoRussian: {
                std::cout << std::endl;

                const char* result = Dictionary::TranslationIntoRussian(dictionary, InputEnglishWord());

                if (!result) {
                    std::cout << "Такого слова нет в словаре!" << std::endl;

                } else {
                    std::cout << "Перевод: " << result << std::endl;
                }
                std::cout << std::endl;
                break;
            }
            case Task::TranslationIntoEnglish: {
                std::cout << std::endl;
                const char* result = Dictionary::TranslationIntoEnglish(dictionary, InputRussianWord());
                if (!result) {
                    std::cout << "Такого слова нет в словаре!" << std::endl;

                } else {
                    std::cout << "Перевод: " << result << std::endl;
                }
                std::cout << std::endl;
                break;
            }
            case Task::PrintDictionary: {
                Dictionary::PrintDictionary(dictionary);
                break;
            }
            case Task::SaveDictionaryIntoFile: {
                Dictionary::SaveDictionaryIntoFile(dictionary);
                std::cout << "Словарь сохранен в файл\n\n";
                break;
            }
            case Task::Exit:
                return 1;
        }
        return 0;
    }
    void LaunchApp() {
        Dictionary::Dictionary dictionary = Dictionary::MakeFromFile();

        bool isRunning = true;
        while (isRunning) {
            std::cout << "1. Добавить слово" << std::endl;
            std::cout << "2. Удалить слово" << std::endl;
            std::cout << "3. Перевести с английского на русский" << std::endl;
            std::cout << "4. Перевести с русского на английский" << std::endl;
            std::cout << "5. Вывести словарь" << std::endl;
            std::cout << "6. Сохранить словарь в файл" << std::endl;
            std::cout << "7. Выход" << std::endl;
            int userChoice{};
            std::cout << std::endl;
            std::cout << "Ваш выбор: ";
            std::cin >> userChoice;
            ClearCin();
            if (RunTask(dictionary, static_cast<Task>(userChoice)) == 1) {
                isRunning = false;
            }
        }
    }
}
