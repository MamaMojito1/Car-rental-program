#ifndef Date_h
#define Date_h

#include "Storable.cpp"

#include <ctime>
#include <string>

typedef struct Date : Serializable
{
private:
    struct tm date;

    bool empty;

public:
    Date(std::string date);

    Date();

    Date operator + (int days);

    bool operator > (Date date) const;

    bool operator >= (Date date) const;

    bool operator < (Date date) const;

    bool operator <= (Date date) const;

    bool isEmpty() const;

    std::string toString() const;
} Date;

#endif