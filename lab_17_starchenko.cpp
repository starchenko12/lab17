#include <iostream>
#include <string>
using namespace std;

class Date {
private:
    int year;
    int month;
    int day;

    bool isLeapYear(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    int daysInMonth(int month, int year) const {
        switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return -1; // Invalid month
        }
    }

    bool validateDate(int year, int month, int day) const {
        if (year < 0) return false;
        if (month < 1 || month > 12) return false;
        if (day < 1 || day > daysInMonth(month, year)) return false;
        return true;
    }

public:
    Date(int year, int month, int day) {
        if (validateDate(year, month, day)) {
            this->year = year;
            this->month = month;
            this->day = day;
        }
        else {
            cout << "Invalid date entered!" << endl;
            this->year = 0;
            this->month = 1;
            this->day = 1;
        }
    }

    void setYear(int year) {
        if (validateDate(year, this->month, this->day)) {
            this->year = year;
        }
        else {
            cout << "Invalid year entered!" << endl;
        }
    }

    void setMonth(int month) {
        if (validateDate(this->year, month, this->day)) {
            this->month = month;
        }
        else {
            cout << "Invalid month entered!" << endl;
        }
    }

    void setDay(int day) {
        if (validateDate(this->year, this->month, day)) {
            this->day = day;
        }
        else {
            cout << "Invalid day entered!" << endl;
        }
    }

    void addDays(int days) {
        while (days > 0) {
            int daysInCurrentMonth = daysInMonth(this->month, this->year);
            if (this->day + days <= daysInCurrentMonth) {
                this->day += days;
                break;
            }
            else {
                days -= (daysInCurrentMonth - this->day + 1);
                this->day = 1;
                if (this->month == 12) {
                    this->month = 1;
                    this->year++;
                }
                else {
                    this->month++;
                }
            }
        }
    }

    void addMonths(int months) {
        int newMonth = this->month + months;
        this->year += newMonth / 12;
        this->month = newMonth % 12;
        if (this->month == 0) {
            this->month = 12;
            this->year--;
        }
        if (this->day > daysInMonth(this->month, this->year)) {
            this->day = daysInMonth(this->month, this->year);
        }
    }

    void addYears(int years) {
        this->year += years;
        if (this->month == 2 && this->day == 29 && !isLeapYear(this->year)) {
            this->day = 28;
        }
    }

    void displayDate() const {
        cout << "Date: " << year << "-" << (month < 10 ? "0" : "") << month << "-" << (day < 10 ? "0" : "") << day << endl;
    }

    int getYear() const {
        return year;
    }

    int getMonth() const {
        return month;
    }

    int getDay() const {
        return day;
    }
};

class Weekday : public Date {
private:
    string getDayOfWeek(int y, int m, int d) const {
        static const string daysOfWeek[] = { "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" };
        if (m < 3) {
            m += 12;
            y--;
        }
        int K = y % 100;
        int J = y / 100;
        int f = d + 13 * (m + 1) / 5 + K + K / 4 + J / 4 + 5 * J;
        return daysOfWeek[f % 7];
    }

public:
    Weekday(int year, int month, int day) : Date(year, month, day) {}

    void displayDayOfWeek() const {
        cout << "Day of the week: " << getDayOfWeek(getYear(), getMonth(), getDay()) << endl;
    }
};

int main() {
    int year, month, day;

    cout << "Enter year: ";
    cin >> year;
    cout << "Enter month: ";
    cin >> month;
    cout << "Enter day: ";
    cin >> day;

    Date date(year, month, day);
    date.displayDate();

    cout << "Enter a new year: ";
    cin >> year;
    date.setYear(year);
    date.displayDate();

    cout << "Enter a new month: ";
    cin >> month;
    date.setMonth(month);
    date.displayDate();

    cout << "Enter a new day: ";
    cin >> day;
    date.setDay(day);
    date.displayDate();

    int daysToAdd, monthsToAdd, yearsToAdd;
    cout << "Enter days to add: ";
    cin >> daysToAdd;
    date.addDays(daysToAdd);
    date.displayDate();

    cout << "Enter months to add: ";
    cin >> monthsToAdd;
    date.addMonths(monthsToAdd);
    date.displayDate();

    cout << "Enter years to add: ";
    cin >> yearsToAdd;
    date.addYears(yearsToAdd);
    date.displayDate();

    Weekday weekday(date.getYear(), date.getMonth(), date.getDay());
    weekday.displayDate();
    weekday.displayDayOfWeek();

    return 0;
}
