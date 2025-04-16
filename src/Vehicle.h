#ifndef vehicle_h
#define vehicle_h

#include "Date.h"
#include "Storable.cpp"

#include <string>

typedef enum
{
    bike = 1,
    car = 2,
    towera = 3
} VehicleType;

class Vehicle : public Storable
{
private:
    std::string registrationNumber;

    VehicleType type;

    int seats;

    std::string companyName;

    double pricePerKm;

    Date PUCExpirationDate;

public:
    Vehicle(std::string registrationNumber, VehicleType type, int seats, std::string companyName, double pricePerKm, Date PUCExpirationDate, long recordId = 0);

    std::string getRegistrationNumber() const;

    VehicleType getVehicleType() const;

    std::string getVehicleTypeName() const;

    int getSeats() const;

    std::string getCompanyName() const;

    double getPricePerKm() const;

    Date getPUCExpirationDate() const;

    void setPricePerKm(double newPrice);

    void Display() const;

    std::string toString() const;

    void setDataFrom(Storable* s);
};

#endif