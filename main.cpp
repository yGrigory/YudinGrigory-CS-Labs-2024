#include <iostream>

namespace {
const int kMinHours = 0;
const int kMaxHours = 23;

const int kMinMinutes = 0;
const int kMaxMinutes = 59;

const int kNightBegin = 0;
const int kMorningBegin = 5;
const int kNoonBegin = 12;
const int kEveningBegin = 18;

const int kBeginDay = 0;
const int kMiddleDay = 12;
const int kEndDay = 23;

const int kDecimalNumericBase = 10;

const int kTwelveHourFormatBase = 12;

const int kHourNominativeSingular = 1;
const int kHoursGenitiveSingularBegin = 2;
const int kHoursGenitiveSingularEnd = 4;
const int kHoursGenitivePluralBegin = 5;
const int kHoursGenitivePluralEnd = 12;
const int kHoursGenitivePlural = 0;

const int kMinuteNominativeSingular = 1;
const int kMinutesGenitiveSingularBegin = 2;
const int kMinutesGenitiveSingularEnd = 4;
const int kMinutesGenitivePluralBegin = 11;
const int kMinutesGenitivePluralEnd = 14;
}  // namespace

int main(int, char**) {
    int hours = 0;
    int minutes = 0;
    std::cout << "введите часы (от 0 до 23) и минуты ( от 0 до 59) через пробел " << std::endl;
    std::cin >> hours >> minutes;
    if ((hours < kMinHours || hours > kMaxHours) || (minutes < kMinMinutes || minutes > kMaxMinutes)) {
        std::cout << "введены недопустимые данные" << std::endl;
        return 1;
    }

    if ((hours == kBeginDay) && (minutes == kMinMinutes)) {
        std::cout << "полночь" << std::endl;
        return 0;
    }

    if ((hours == kMiddleDay) && (minutes == kMinMinutes)) {
        std::cout << "полдень" << std::endl;
        return 0;
    }

    int hoursTwelveHoursFormat = (hours > kMiddleDay) ? (hours % kTwelveHourFormatBase) : hours;

    std::cout << hoursTwelveHoursFormat;
    if (hoursTwelveHoursFormat == kHourNominativeSingular) {
        std::cout << " час";
    } else if ((hoursTwelveHoursFormat >= kHoursGenitiveSingularBegin) && (hoursTwelveHoursFormat <= kHoursGenitiveSingularEnd)) {
        std::cout << " часа";
    } else if (((hoursTwelveHoursFormat >= kHoursGenitivePluralBegin) && (hoursTwelveHoursFormat <= kHoursGenitivePluralEnd)) ||
               hoursTwelveHoursFormat == kHoursGenitivePlural) {
        std::cout << " часов";
    }

    if (minutes != kMinMinutes) {
        std::cout << ' ' << minutes;

        int lastDigitMinutes = minutes % kDecimalNumericBase;
        if ((lastDigitMinutes == kMinuteNominativeSingular) && (minutes != kMinutesGenitivePluralBegin)) {
            std::cout << " минута";
        } else if ((lastDigitMinutes >= kMinutesGenitiveSingularBegin) && (lastDigitMinutes <= kMinutesGenitiveSingularEnd) &&
                   (minutes < kMinutesGenitivePluralBegin || minutes > kMinutesGenitivePluralEnd)) {
            std::cout << " минуты";
        } else {
            std::cout << " минут";
        }
    }

    if ((hours >= kMorningBegin) && (hours < kNoonBegin)) {
        std::cout << " утра";
    } else if ((hours >= kNoonBegin) && (hours < kEveningBegin)) {
        std::cout << " дня";
    } else if ((hours >= kEveningBegin) && (hours <= kEndDay)) {
        std::cout << " вечера";
    } else if ((hours >= kNightBegin) && (hours < kMorningBegin)) {
        std::cout << " ночи";
    }

    if (minutes == kMinMinutes) {
        std::cout << " ровно";
    }

    std::cout << std::endl;
    return 0;
}
