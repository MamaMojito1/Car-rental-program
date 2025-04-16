#include "Date.h"
#include "string_helper.h"

const char DELIMITER = '/';

Date :: Date()
{
    time_t now = time(NULL);
    this->empty = false;
    this->date = *localtime(&now);
}

Date :: Date(std::string date)
{
    if(date.length() < 8)
    {
        this->empty = true;
        return;
    }

    this->empty = false;

    std::vector<std::string> dateComponents = split(date, DELIMITER);

	int day = 0, month = 0, year = 0;

	try {
		day = std::stoi(dateComponents[0]);
		month = std::stoi(dateComponents[1]);
		year = std::stoi(dateComponents[2]);

		if (day == 0 || month == 0 || year == 0) {
			std::cerr << "Error: One or more date components are zero (invalid input)." << std::endl;
		}
	}
	catch (const std::invalid_argument&) {
		std::cout << "Error: Invalid argument. Non-numeric value in date components." << std::endl;
	}
	catch (const std::out_of_range&) {
		std::cout << "Error: One or more date components are out of int range." << std::endl;
	}

    time_t now = time(NULL);
    this->date = *localtime(&now);

    this->date.tm_year = year - 1900;
    this->date.tm_mon = month - 1;
    this->date.tm_mday = day;

    mktime(&this->date);
}

bool Date::isEmpty() const
{
    return this->empty;
}

std::string Date::toString() const
{
    if(this->empty)
    {
        return "";
    }
    std::stringstream ss;
    ss << this->date.tm_mday << "/" << this->date.tm_mon + 1 << "/" << this->date.tm_year + 1900;    
    return ss.str();
}

Date Date::operator + (int days)
{
    Date newDate = *this;

    if(newDate.isEmpty())
    {
        return newDate;
    }

    newDate.date.tm_mday += days;

    time_t adjustedDate = mktime(&newDate.date);

    newDate.date = *localtime(&adjustedDate);
    return newDate;
}

bool Date::operator > (Date date) const
{
    if(this->isEmpty() || date.isEmpty())
    {
        return false;
    }

    int yearDiff = this->date.tm_year - date.date.tm_year;
    int monthDiff = this->date.tm_mon - date.date.tm_mon;
    int dayDiff = this->date.tm_mday - date.date.tm_mday;

    if(yearDiff != 0)
    {
        return yearDiff > 0;
    }
    else if(monthDiff != 0)
    {
        return monthDiff > 0;
    }
    else
    {
        return dayDiff > 0;
    }
}

bool Date::operator >= (Date date) const
{
    return !(*this < date);
}

bool Date::operator < (Date date) const
{
    if(this->isEmpty() || date.isEmpty())
    {
        return false;
    }

    int yearDiff = this->date.tm_year - date.date.tm_year;
    int monthDiff = this->date.tm_mon - date.date.tm_mon;
    int dayDiff = this->date.tm_mday - date.date.tm_mday;

    if(yearDiff != 0) return yearDiff < 0;
    if(monthDiff != 0) return monthDiff < 0;
    else return dayDiff < 0;
}

bool Date::operator <= (Date date) const
{
    return !(*this > date);
}


