#include <iostream>

namespace {
const int kMinHoursValue = 0;
const int kMaxHoursValue = 23;

const int kMinMinutesValue = 0;
const int kMaxMinutesValue = 59;

const int kMidDayHoursValue = 12;
const int kMidDayMinutesValue = 0;

const int kMidNightHoursValue = 0;
const int kMidNightMinutesValue = 0;

const int kDecimalBase = 10;
const int kDuodecimalBase = 12;

const int kHoursValueInNominativeCase = 1;

const int kMinHoursValueInGenetiveCaseSingular = 2;
const int kMaxHoursValueInGenetiveCaseSingular = 4;

const int kMinHoursValueInGenetiveCasePlural = 5;
const int kMaxHoursValueInGenetiveCasePlural = 12;
const int kAdditionalHoursValueInGenetiveCasePlural = 0;

const int kValueOfTensPlaceInMinutesException = 1;

const int kDecimalBasedMinutesValueInNominativeCase = 1;

const int kMinMinutesValueInGenetiveCaseSingular = 2;
const int kMaxMinutesValueInGenetiveCaseSingular = 4;

const int kMinMinutesValueInGenetiveCasePlural = 5;
const int kMaxMinutesValueInGenetiveCasePlural = 9;

const int kMorningMinHoursValue = 5;
const int kMorningMaxHoursValue = 11;

const int kAfternoonMinHoursValue = 12;
const int kAfternoonMaxHoursValue = 17;

const int kEveningMinHoursValue = 18;
const int kEveningMaxHoursValue = 23;

const int kNightMinHoursValue = 0;
const int kNightMaxHoursValue = 4;
}  // namespace

int main(int, char**) {
    int hours = 0;
    int minutes = 0;
    int duodecimalBasedHours = 0;
    int decimalBasedMinutes = 0;
    int valueOfTensPlaceInMinutes = 0;

    std::cout << "Введите числовое значение часов от 0 до 23 и минут от 0 до 59" << std::endl;
    std::cin >> hours >> minutes;

    if ((hours > kMaxHoursValue || hours < kMinHoursValue) || (minutes > kMaxMinutesValue || minutes < kMinMinutesValue)) {
        std::cout << "Ошибка ввода" << std::endl;
        return 1;
    }
    if (hours == kMidDayHoursValue && minutes == kMidDayMinutesValue) {
        std::cout << "Полдень" << std::endl;
        return 0;
    }
    if (hours == kMidNightHoursValue && minutes == kMidNightMinutesValue) {
        std::cout << "Полночь" << std::endl;
        return 0;
    }

    if (hours == kMidDayHoursValue) {
        duodecimalBasedHours = hours;
    } else {
        duodecimalBasedHours = hours % kDuodecimalBase;
    }

    std::cout << duodecimalBasedHours;

    if (duodecimalBasedHours == kHoursValueInNominativeCase) {
        std::cout << " час ";
    }
    if (duodecimalBasedHours >= kMinHoursValueInGenetiveCaseSingular && duodecimalBasedHours <= kMaxHoursValueInGenetiveCaseSingular) {
        std::cout << " часа ";
    }
    if ((duodecimalBasedHours >= kMinHoursValueInGenetiveCasePlural && duodecimalBasedHours <= kMaxHoursValueInGenetiveCasePlural) ||
        duodecimalBasedHours == kAdditionalHoursValueInGenetiveCasePlural) {
        std::cout << " часов ";
    }

    decimalBasedMinutes = minutes % kDecimalBase;
    valueOfTensPlaceInMinutes = minutes / kDecimalBase;

    if (minutes != kMinMinutesValue) {
        std::cout << minutes;
    }

    if (decimalBasedMinutes == kDecimalBasedMinutesValueInNominativeCase && valueOfTensPlaceInMinutes != kValueOfTensPlaceInMinutesException) {
        std::cout << " минута ";
    }
    if ((decimalBasedMinutes >= kMinMinutesValueInGenetiveCaseSingular && decimalBasedMinutes <= kMaxMinutesValueInGenetiveCaseSingular) &&
        valueOfTensPlaceInMinutes != kValueOfTensPlaceInMinutesException) {
        std::cout << " минуты ";
    }
    if ((decimalBasedMinutes >= kMinMinutesValueInGenetiveCasePlural && decimalBasedMinutes <= kMaxMinutesValueInGenetiveCasePlural) ||
        valueOfTensPlaceInMinutes == kValueOfTensPlaceInMinutesException) {
        std::cout << " минут ";
    }

    if (hours >= kMorningMinHoursValue && hours <= kMorningMaxHoursValue) {
        std::cout << "утра";
    }
    if (hours >= kAfternoonMinHoursValue && hours <= kAfternoonMaxHoursValue) {
        std::cout << "дня";
    }
    if (hours >= kEveningMinHoursValue && hours <= kEveningMaxHoursValue) {
        std::cout << "вечера";
    }
    if (hours >= kNightMinHoursValue && hours <= kNightMinHoursValue) {
        std::cout << "ночи";
    }

    if (minutes == kMinMinutesValue) {
        std::cout << " ровно";
    }

    std::cout << std::endl;

    return 0;
}
