#include "Vehicle.h"
#include "string_helper.h"

const char DELIMITER = ';';

Vehicle::Vehicle(std::string registrationNumber, VehicleType type, int seats, 
    std::string companyName, double pricePerKm, Date PUCExpirationDate, 
    long recordId) : Storable(recordId)
{
    this->registrationNumber = registrationNumber;
    this->type = type;
    this->seats = seats;
    this->companyName = companyName;
    this->pricePerKm = pricePerKm;
    this->PUCExpirationDate = PUCExpirationDate;
}

std::string Vehicle::getRegistrationNumber() const
{
    return this->registrationNumber;
}

VehicleType Vehicle::getVehicleType() const
{
    return this->type;
}

int Vehicle::getSeats() const
{
    return this->seats;
}

std::string Vehicle::getCompanyName() const 
{
    return this->companyName;
}

double Vehicle::getPricePerKm() const
{
    return this->pricePerKm;
}

Date Vehicle::getPUCExpirationDate() const
{
    return this->PUCExpirationDate;
}

void Vehicle::setPricePerKm(double newPrice)
{
    this->pricePerKm = newPrice;
}

std::string Vehicle::getVehicleTypeName() const
{
    switch(this->type)
    {
    case VehicleType::bike:
        return "Bike";
    case VehicleType::car:
        return "Car";
    case VehicleType::towera:
        return "Towera";
    default:
        return "";
    }
}

void Vehicle::Display() const
{
    std::cout << "Vehicle Details: "      << std::endl;
    std::cout << "Registration no : "     << this->registrationNumber << std::endl;
    std::cout << "Vehicle type : "        << this->getVehicleTypeName() << std::endl;
    std::cout << "No of seats : "         << this->seats << std::endl;
    std::cout << "Company name : "        << this->companyName << std::endl;
    std::cout << "Price per km : "        << this->pricePerKm << std::endl;
    std::cout << "PUC Expiration date : " << this->PUCExpirationDate.toString() << std::endl;
}

std::string Vehicle::toString() const
{
    std::stringstream ss;
    ss << recordId << DELIMITER
       << registrationNumber << DELIMITER
       << type << DELIMITER
       << seats << DELIMITER
       << companyName << DELIMITER
       << std::to_string(pricePerKm) << DELIMITER
       << PUCExpirationDate.toString();
       
    return ss.str();
}

void Vehicle::setDataFrom(Storable* s)
{
    Vehicle* v = dynamic_cast<Vehicle*>(s);

    if(v)
    {
        this->registrationNumber = v->registrationNumber;
        this->type = v->type;
        this->seats = v->seats;
        this->companyName = v->companyName;
        this->pricePerKm = v->pricePerKm;
        this->PUCExpirationDate = v->PUCExpirationDate;
    }
}