#include <iostream>

namespace {
const int kMinHours = 0;
const int kMaxHours = 24;

const int kMinMinutes = 0;
const int kMaxMinutes = 60;

const int kMorningMinHours = 5;
const int kMorningMaxHours = 12;

const int kAfternoonMinHours = 12;
const int kAfternoonMaxHours = 18;

const int kEveningMinHours = 18;
const int kEveningMaxHours = 23;

const int kNightMinHours = 0;
const int kNightMaxHours = 5;

const int kMidDayHours = 12;
const int kMidDayMinutes = 0;

const int kMidNightHours = 0;
const int kMidNightMinutes = 0;

const int kHoursTimeRange = 12;
const int kMinutesTimeRange = 10;

const int kNightStartHours = 1;

const int kDayHoursBorder = 5;

const int kMinutesEnds1 = 1;
const int kMinutesEnds2 = 2;
const int kMinutesEnds3 = 3;
const int kMinutesEnds4 = 4;
const int kMinutesEnds5 = 5;
const int kMinutesEnds6 = 6;
const int kMinutesEnds7 = 7;
const int kMinutesEnds8 = 8;
const int kMinutesEnds9 = 9;
}  // namespace

int main(int, char**) {
    int hours = 0;
    int minutes = 0;
    int dayHours = 0;
    int dayMinutes = 0;

    std::cin >> hours >> minutes;

    if ((kMinHours > hours || hours >= kMaxHours) || (kMinMinutes > minutes || minutes >= kMaxMinutes)) {
        std::cout << "Ошибка ввода" << std::endl;
        return 1;
    }
    if (hours == kMidDayHours && minutes == kMidDayMinutes) {
        std::cout << "Полдень" << std::endl;
        return 0;
    }
    if (hours == kMidNightHours && minutes == kMidNightMinutes) {
        std::cout << "Полночь" << std::endl;
        return 0;
    }

    if (hours == kMidDayHours) {
        dayHours = hours;
    } else {
        dayHours = hours % kHoursTimeRange;
    }

    std::cout << dayHours;

    if (dayHours == kNightStartHours) {
        std::cout << " час ";
    }
    if (dayHours > kNightStartHours && dayHours < kDayHoursBorder) {
        std::cout << " часа ";
    }
    if (dayHours >= kDayHoursBorder || dayHours == kMidNightHours) {
        std::cout << " часов ";
    }
    if (minutes == kMinMinutes) {
        if (hours >= kMorningMinHours && hours < kMorningMaxHours) {
            std::cout << "утра ";
        }
        if (hours >= kAfternoonMinHours && hours < kAfternoonMaxHours) {
            std::cout << "дня ";
        }
        if (hours >= kEveningMinHours && hours <= kEveningMaxHours) {
            std::cout << "вечера ";
        }
        if (hours > kNightMinHours && hours < kNightMaxHours) {
            std::cout << "ночи ";
        }
        std::cout << "ровно" << std::endl;
        return 0;
    }

    dayMinutes = minutes % kMinutesTimeRange;
    std::cout << minutes;

    if (dayMinutes == kMinutesEnds1) {
        std::cout << " минута ";
    }
    if (((dayMinutes == kMinutesEnds2 || dayMinutes == kMinutesEnds3 || dayMinutes == kMinutesEnds4) &&
         minutes / kMinutesTimeRange == kMinutesEnds1) ||
        dayMinutes == kMinutesEnds5 || dayMinutes == kMinutesEnds6 || dayMinutes == kMinutesEnds7 || dayMinutes == kMinutesEnds8 ||
        dayMinutes == kMinutesEnds9) {
        std::cout << " минут ";
    }
    if ((dayMinutes == kMinutesEnds2 || dayMinutes == kMinutesEnds3 || dayMinutes == kMinutesEnds4) && minutes / kMinutesTimeRange != kMinutesEnds1) {
        std::cout << " минуты ";
    }

    if (hours >= kMorningMinHours && hours < kMorningMaxHours) {
        std::cout << "утра" << std::endl;
        return 0;
    }
    if (hours >= kAfternoonMinHours && hours < kAfternoonMaxHours) {
        std::cout << "дня" << std::endl;
        return 0;
    }
    if (hours >= kEveningMinHours && hours <= kEveningMaxHours) {
        std::cout << "вечера" << std::endl;
        return 0;
    }
    if (hours > kNightMinHours && hours < kNightMaxHours) {
        std::cout << "ночи" << std::endl;
        return 0;
    }
}
