#include "Trip.h"
#include "string_helper.h"

#include <iostream>

const char DELIMITER = ';';

Trip::Trip(const Vehicle* vehicle, const User* user, Date startDate, Date endDate, 
    long recordId, long startReading, long endReading, 
    double fare, bool completed) : Storable(recordId)
{
    this->vehicle = vehicle;
    this->user = user;
    this->startDate = startDate;
    this->endDate = endDate;
    this->recordId = recordId;
    this->startReading = startReading;
    this->endReading = endReading;
    this->fare = fare;
    this->completed = completed;
}

const User& Trip::getUser() const {return *this->user; }

const Vehicle& Trip::getVehicle() const { return *this->vehicle; }

Date Trip::getStartDate() const { return this->startDate; }

Date Trip::getEndDate() const { return this->endDate; }

long Trip::getStartReading() const { return this->startReading; }

long Trip::getEndReading() const { return this->endReading; }

long Trip::getFare() const { return this->fare; }

bool Trip::isCompleted() const { return this->completed; }

void Trip::startTrip(long startReading)
{
    this->startReading = startReading;
}

double Trip::completeTrip(long endReading)
{
    if(this->completed)
    {
        return this->fare;
    }

    this->endReading = endReading;
    this->fare = (this->endReading - this->startReading) * this->vehicle->getPricePerKm();
    this->completed = true;

    return this->fare;
}

void Trip::display() const
{
    std::cout << "Vehicle Details : " << std::endl;
    std::cout << "Registration no : " << this->vehicle->getRegistrationNumber() << std::endl;
    std::cout << "Vehicle type : " << this->vehicle->getVehicleTypeName() << std::endl; 
    std::cout << "Company name : " << this->vehicle->getCompanyName() << std::endl;
    std::cout << "Price per km : " << this->vehicle->getPricePerKm() << " Rs/Km" << std::endl;
    std::cout << std::endl;

    std::cout << "User Details : " << std::endl;
    std::cout << "Name : " << this->user->getName() << std::endl;
    std::cout << "Contact : " << this->user->getContact() << std::endl;

    std::cout << std::endl;

    std::cout << "Trip Details : " << std::endl;
    std::cout << "Start date : " << this->startDate.toString() << std::endl;
    std::cout << "End date : " << this->endDate.toString() << std::endl;

    std::string tripStatus = "Not started";

    if(this->startReading != 0)
    {
        tripStatus = "On going";
        std::cout << "Start reading : " << this->startReading << std::endl;
    }
    if(this->completed)
    {
        tripStatus = "Completed";
        std::cout << "End reading : " << this->endReading << std::endl;
        std::cout << "Total run : " << this->endReading - this->startReading << std::endl;
        std::cout << "Total fare : " << this->fare << std::endl;
    }
    std::cout << "Trip status : " << tripStatus << std::endl;
}

std::string Trip::toString() const
{
    std::stringstream ss;
    ss << recordId << DELIMITER
       << vehicle->getRecordId() << DELIMITER
       << user->getRecordId() << DELIMITER
       << startDate.toString() << DELIMITER
       << endDate.toString() << DELIMITER
       << startReading << DELIMITER
       << endReading << DELIMITER
       << fare << DELIMITER
       << completed;
    
    return ss.str();
}

void Trip::setDataFrom(Storable* s)
{
    Trip * t = static_cast<Trip*>(s);

    if(t)
    {
        this->vehicle = t->vehicle;
        this->user = t->user;
        this->startDate = t->startDate;
        this->endDate = t->endDate;
        this->startReading = t->endReading;
        this->endReading = t->endReading;
        this->fare = t->fare;
        this->completed = t->completed;
    }
}