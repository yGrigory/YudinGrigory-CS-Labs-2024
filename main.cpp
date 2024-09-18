#include <iostream>

namespace {
const int minHours = 0;
const int maxHours = 24;

const int minMinutes = 0;
const int maxMinutes = 60;

const int morningMinHours = 5;
const int morningMaxHours = 12;

const int afternoonMinHours = 12;
const int afternoonMaxHours = 18;

const int eveningMinHours = 18;
const int eveningMaxHours = 23;

const int nightMinHours = 0;
const int nightMaxHours = 5;

const int midDayHours = 12;
const int midDayMinutes = 0;

const int midNightHours = 0;
const int midNightMinutes = 0;

const int hoursTimeRange = 12;
const int minutesTimeRange = 10;

const int nightStartHours = 1;

const int dayHoursBorder = 5;

const int minutesEnds1 = 1;
const int minutesEnds2 = 2;
const int minutesEnds3 = 3;
const int minutesEnds4 = 4;
const int minutesEnds5 = 5;
const int minutesEnds6 = 6;
const int minutesEnds7 = 7;
const int minutesEnds8 = 8;
const int minutesEnds9 = 9;
}

int main(int, char**) {
    int hours = 0;
    int minutes = 0;
    int dayHours = 0;
    int dayMinutes = 0;

    std::cin >> hours >> minutes;

    if ((minHours > hours || hours >= maxHours) || (minMinutes > minutes || minutes >= maxMinutes)) {
        std::cout << "Ошибка ввода" << std::endl;
        return 1;
    }
    if (hours == midDayHours && minutes == midDayMinutes) {
        std::cout << "Полдень" << std::endl;
        return 0;
    }
    if (hours == midNightHours && minutes == midNightMinutes) {
        std::cout << "Полночь" << std::endl;
        return 0;
    }

    if (hours == midDayHours) {
        dayHours = hours;
    } else {
        dayHours = hours % hoursTimeRange;
    }

    std::cout << dayHours;

    if (dayHours == nightStartHours) {
        std::cout << " час ";
    }
    if (dayHours > nightStartHours && dayHours < dayHoursBorder) {
        std::cout << " часа ";
    }
    if (dayHours >= dayHoursBorder || dayHours == midNightHours) {
        std::cout << " часов ";
    }
    if (minutes == minMinutes) {
        if (hours >= morningMinHours && hours < morningMaxHours) {
            std::cout << "утра ";
        }
        if (hours >= afternoonMinHours && hours < afternoonMaxHours) {
            std::cout << "дня ";
        }
        if (hours >= eveningMinHours && hours <= eveningMaxHours) {
            std::cout << "вечера ";
        }
        if (hours > nightMinHours && hours < nightMaxHours) {
            std::cout << "ночи ";
        }
        std::cout << "ровно" << std::endl;
        return 0;
    }

    dayMinutes = minutes % minutesTimeRange;
    std::cout << minutes;

    if (dayMinutes == minutesEnds1) {
        std::cout << " минута ";
    }
    if (((dayMinutes == minutesEnds2 || dayMinutes == minutesEnds3 || dayMinutes == minutesEnds4) &&
         minutes / minutesTimeRange == minutesEnds1) ||
        dayMinutes == minutesEnds5 || dayMinutes == minutesEnds6 || dayMinutes == minutesEnds7 || dayMinutes == minutesEnds8 ||
        dayMinutes == minutesEnds9) {
        std::cout << " минут ";
    }
    if ((dayMinutes == minutesEnds2 || dayMinutes == minutesEnds3 || dayMinutes == minutesEnds4) && minutes / minutesTimeRange != minutesEnds1) {
        std::cout << " минуты ";
    }

    if (hours >= morningMinHours && hours < morningMaxHours) {
        std::cout << "утра" << std::endl;
        return 0;
    }
    if (hours >= afternoonMinHours && hours < afternoonMaxHours) {
        std::cout << "дня" << std::endl;
        return 0;
    }
    if (hours >= eveningMinHours && hours <= eveningMaxHours) {
        std::cout << "вечера" << std::endl;
        return 0;
    }
    if (hours > nightMinHours && hours < nightMaxHours) {
        std::cout << "ночи" << std::endl;
        return 0;
    }
}
