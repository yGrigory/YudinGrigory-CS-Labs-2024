#pragma once

namespace Menu {
enum class Task : int {
  AddWord = 1,
  DeleteWord = 2,
  TranslationIntoRussian = 3,
  TranslationIntoEnglish = 4,
  PrintDictionary = 5,
  SaveDictionaryIntoFile = 6,
  Exit = 7
};

void LaunchApp();
}  // namespace Menu
