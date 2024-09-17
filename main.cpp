#include <iostream>

namespace {
const int kminHours = 0;
const int kmaxHours = 24;

const int kminMinutes = 0;
const int kmaxMinutes = 60;

const int kmorningMinHours = 5;
const int kmorningMaxHours = 12;

const int kafternoonMinHours = 12;
const int kafternoonMaxHours = 18;

const int keveningMinHours = 18;
const int keveningMaxHours = 23;

const int knightMinHours = 0;
const int knightMaxHours = 5;

const int kmidDayHours = 12;
const int kmidDayMinutes = 0;

const int kmidNightHours = 0;
const int kmidNightMinutes = 0;

const int khoursTimeRange = 12;
const int kminutesTimeRange = 10;

const int knightStartHours = 1;

const int kdayHoursBorder = 5;

const int kminutesEnds1 = 1;
const int kminutesEnds2 = 2;
const int kminutesEnds3 = 3;
const int kminutesEnds4 = 4;
const int kminutesEnds5 = 5;
const int kminutesEnds6 = 6;
const int kminutesEnds7 = 7;
const int kminutesEnds8 = 8;
const int kminutesEnds9 = 9;
}  // namespace

int main(int, char**) {
    int hours = 0;
    int minutes = 0;
    int dayHours = 0;
    int dayMinutes = 0;

    std::cin >> hours >> minutes;

    if ((kminHours > hours || hours >= kmaxHours) || (kminMinutes > minutes || minutes >= kmaxMinutes)) {
        std::cout << "Ошибка ввода" << std::endl;
        return 1;
    }
    if (hours == kmidDayHours && minutes == kmidDayMinutes) {
        std::cout << "Полдень" << std::endl;
        return 0;
    }
    if (hours == kmidNightHours && minutes == kmidNightMinutes) {
        std::cout << "Полночь" << std::endl;
        return 0;
    }

    if (hours == kmidDayHours) {
        dayHours = hours;
    } else {
        dayHours = hours % khoursTimeRange;
    }

    std::cout << dayHours;

    if (dayHours == knightStartHours) {
        std::cout << " час ";
    }
    if (dayHours > knightStartHours && dayHours < kdayHoursBorder) {
        std::cout << " часа ";
    }
    if (dayHours >= kdayHoursBorder || dayHours == kmidNightHours) {
        std::cout << " часов ";
    }
    if (minutes == kminMinutes) {
        if (hours >= kmorningMinHours && hours < kmorningMaxHours) {
            std::cout << "утра ";
        }
        if (hours >= kafternoonMinHours && hours < kafternoonMaxHours) {
            std::cout << "дня ";
        }
        if (hours >= keveningMinHours && hours <= keveningMaxHours) {
            std::cout << "вечера ";
        }
        if (hours > knightMinHours && hours < knightMaxHours) {
            std::cout << "ночи ";
        }
        std::cout << "ровно" << std::endl;
        return 0;
    }

    dayMinutes = minutes % kminutesTimeRange;
    std::cout << minutes;

    if (dayMinutes == kminutesEnds1) {
        std::cout << " минута ";
    }
    if (((dayMinutes == kminutesEnds2 || dayMinutes == kminutesEnds3 || dayMinutes == kminutesEnds4) && minutes / kminutesTimeRange == kminutesEnds1) ||
        dayMinutes == kminutesEnds5 || dayMinutes == kminutesEnds6 || dayMinutes == kminutesEnds7 || dayMinutes == kminutesEnds8 ||
        dayMinutes == kminutesEnds9) {
        std::cout << " минут ";
    }
    if ((dayMinutes == kminutesEnds2 || dayMinutes == kminutesEnds3 || dayMinutes == kminutesEnds4) && minutes / kminutesTimeRange != kminutesEnds1) {
        std::cout << " минуты ";
    }

    if (hours >= kmorningMinHours && hours < kmorningMaxHours) {
        std::cout << "утра" << std::endl;
        return 0;
    }
    if (hours >= kafternoonMinHours && hours < kafternoonMaxHours) {
        std::cout << "дня" << std::endl;
        return 0;
    }
    if (hours >= keveningMinHours && hours <= keveningMaxHours) {
        std::cout << "вечера" << std::endl;
        return 0;
    }
    if (hours > knightMinHours && hours < knightMaxHours) {
        std::cout << "ночи" << std::endl;
        return 0;
    }
}
