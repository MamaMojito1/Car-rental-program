#include "Application.h"
#include "database_templates.cpp"

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <limits>

Application::Application()
{
    try
    {
        this->db = new Database();
    }
    catch(Error e)
    {
        std::cout << e.getMessage();
        exit(EXIT_FAILURE);
    }
}

void Application::gotoXY(int x, int y) const
{
    printf("%c[%d;%df", 0x1B, y, x);
}


void Application::renderMenu()
{
    unsigned char choice = 1;
    while(true)
    {
        system("cls");
        
        gotoXY(25, 4);
        std::cout << "Select any option from below: ";
        gotoXY(25, 5);
        std::cout << "1. Add new vehicle";
        gotoXY(25, 6);
        std::cout << "2. View vehicle details";
        gotoXY(25, 7);
        std::cout << "3. Edit vehicle details";
        gotoXY(25, 8);
        std::cout << "4. Add new user";
        gotoXY(25, 9);
        std::cout << "5. Add new trip";
        gotoXY(25, 10);
        std::cout << "6. View trip";
        gotoXY(25, 11);
        std::cout << "7. Start trip";
        gotoXY(25, 12);
        std::cout << "8. Complete trip";
        gotoXY(25, 13);
        std::cout << "9. Exit";
        
        gotoXY(30, 15);
        std::cout << "Enter your choice: ";
        gotoXY(50, 15);
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
		switch (choice)
		{
		case '1':
			this->renderAddNewVehicleMenu();
			break;
		case '2':
			this->renderViewVehicleMenu();
			break;
		case '3':
			this->renderEditVehicleMenu();
			break;
		case '4':
			this->renderAddNewUserMenu();
			break;
		case '5':
			this->renderAddNewTripMenu();
			break;
		case '6':
			this->renderViewTripMenu();
			break;
		case '7':
			this->renderStartTripMenu();
			break;
		case '8':
			this->renderCompleteTripMenu();
			break;
		case '9':
			this->cleanMemory();
			system("cls");
			exit(EXIT_SUCCESS);
			break;
		default:
			this->cleanMemory();
			system("cls");
			exit(EXIT_SUCCESS);
			break;
		}
    }
}

void Application::renderAddNewVehicleMenu() const
{
    std::string header = "Enter details of vehicle (All fields are required) ";
    std::string registrationNoLabel = "Enter vehicle registration number : ";
    std::string vehicleTypeLabel = "Enter vehicle type : ";
    std::string vehicleOptionLabel = "(1. Bike, 2. Car, 3. Towera)";
    std::string seatLabel = "Enter no. of seats : ";
    std::string companyNameLabel = "Enter name of company : ";
    std::string priceLabel = "Enter price per km : ";
    std::string pucExpirationDateLabel = "Enter PUC expiration date (d/m/yyyy) : ";

    std::string registrationNo;
    int vehicleType;
    int seats;
    std::string companyName;
    double price;
    std::string pucExpirationDate;

    system("cls");

    gotoXY(0, 1);
    std::cout << header;

	gotoXY(0, 3);
	std::cout << registrationNoLabel;

	gotoXY(0, 4);
	std::cout << vehicleTypeLabel;

	gotoXY(0, 5);
	std::cout << vehicleOptionLabel;

	gotoXY(0, 6);
	std::cout << seatLabel;

	gotoXY(0, 7);
	std::cout << companyNameLabel;

	gotoXY(0, 8);
	std::cout << priceLabel;

	gotoXY(0, 9);
	std::cout << pucExpirationDateLabel;

	gotoXY(int(registrationNoLabel.length()), 3);
	std::getline(std::cin, registrationNo);

	gotoXY(int(vehicleTypeLabel.length()), 4);
	std::cin >> vehicleType;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	gotoXY(int(seatLabel.length()), 6);
	std::cin >> seats;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	gotoXY(int(companyNameLabel.length()), 7);
	std::getline(std::cin, companyName);

	gotoXY(int(priceLabel.length()), 8);
	std::cin >> price;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	gotoXY(int(pucExpirationDateLabel.length()), 9);
	std::getline(std::cin, pucExpirationDate);

	Vehicle * vehicle;

	try
	{
		vehicle = new Vehicle(registrationNo, VehicleType(vehicleType), seats, companyName, price, Date(pucExpirationDate));
		this->db->addNewRecord(vehicle);
		std::stringstream ss;
	
		ss << "Vehicle Id : " << vehicle->getRecordId();
		showDialog("Vehicle added successfully", ss.str());
	}
	catch (Error e)
	{
		showDialog(e.getMessage());
	}

	delete vehicle;
}

void Application::renderViewVehicleMenu() const
{
	std::string header = "Enter registration no. of vehicle : ";
	std::string registrationNo;

	system("cls");

	gotoXY(0, 1);
	std::cout << header;

	gotoXY(int(header.length()), 1);
	std::getline(std::cin, registrationNo);

	gotoXY(0, 3);
	try
	{
		auto vehicle = this->db->getVehicle(registrationNo);
		vehicle->Display();

		std::cout << std::endl << "Press any key to continue";
		std::cin.get();
	}
	catch (Error e)
	{
		this->showDialog(e.getMessage());
	}
}

void Application::renderEditVehicleMenu() const
{
	std::string header = "Enter registration no. of vehicle you want to edit : ";
	std::string priceLabel = "Enter new price per km : ";
	std::string registrationNo;

	system("cls");

	gotoXY(0, 1);
	std::cout << header;

	gotoXY(int(header.length()), 1);
	std::getline(std::cin, registrationNo);

	gotoXY(0, 3);
	Vehicle * modifiedVehicle;

	try
	{
		auto vehicle = this->db->getVehicle(registrationNo);
		modifiedVehicle = new Vehicle(*vehicle);
		vehicle->Display();

		std::string newPrice;
		
		gotoXY(0, 12);
		std::cout << priceLabel;

		gotoXY(int(priceLabel.length()), 12);
		std::getline(std::cin, newPrice);

		if (newPrice != "")
		{
			modifiedVehicle->setPricePerKm(stod(newPrice));

			this->db->updateRecord(modifiedVehicle);

			this->showDialog("Vehicle data updated successfully");
		}
	}
	catch (Error e)
	{
		this->showDialog(e.getMessage());
	}
	delete modifiedVehicle;

}

void Application::renderAddNewUserMenu() const
{
	std::string header = "Enter details of user ";
	std::string userNameLabel = "Enter name of user : ";
	std::string userContactLabel = "Enter contact no. of user : ";
	std::string userEmailLabel = "Enter email of user (optional) : ";

	std::string name;
	std::string contact;
	std::string email;

	system("cls");
	gotoXY(0, 1);
	std::cout << header;

	gotoXY(0, 3);
	std::cout << userNameLabel;

	gotoXY(0, 4);
	std::cout << userContactLabel;

	gotoXY(0, 5);
	std::cout << userEmailLabel;

	gotoXY(int(userNameLabel.length()), 3);
	std::getline(std::cin, name);

	gotoXY(int(userContactLabel.length()), 4);
	std::getline(std::cin, contact);

	gotoXY(int(userEmailLabel.length()), 5);
	std::getline(std::cin, email);

	User * user;
	try
	{
		user = new User(name, contact, email);
		this->db->addNewRecord(user);
		std::stringstream ss;
		ss << "User Id : " << user->getRecordId();
		showDialog("User added successfully", ss.str());
	}
	catch (Error e)
	{
		showDialog(e.getMessage());
	}
	delete user;
}

void Application::renderAddNewTripMenu() const
{
	std::string header = "Enter details of trip (All fields are required) ";
	std::string userContactLabel = "Enter contact no. of user : ";
	std::string startDateLabel = "Enter start date of trip (d/m/yyyy) : ";
	std::string endDateLabel = "Enter end date of trip (d/m/yyyy) : ";
	std::string vehicleTypeLabel = "Enter vehicle type : ";
	std::string vehicleOptionLabel = "(1. Bike, 2. Car, 3. Towera)";
	std::string registrationNoLabel = "Enter registration no. of vehicle : ";

	std::string contactNo;
	std::string startDate;
	std::string endDate;
	int vehicleType;

	std::string registrationNo;

	const User * user;
	const Vehicle * vehicle;

	system("cls");

	gotoXY(0, 1);
	std::cout << userContactLabel;

	gotoXY(int(userContactLabel.length()), 1);
	std::getline(std::cin, contactNo);

	try
	{
		user = this->db->getUser(contactNo);
		gotoXY(0, 3);
		std::cout << "User found : " << user->getName();
	}
	catch (Error e)
	{
		this->showDialog(e.getMessage());
	}

	gotoXY(0, 5);
	std::cout << header;

	gotoXY(0, 7);
	std::cout << startDateLabel;

	gotoXY(0, 8);
	std::cout << endDateLabel;

	gotoXY(0, 9);
	std::cout << vehicleTypeLabel;
	
	gotoXY(0, 10);
	std::cout << vehicleOptionLabel;

	gotoXY(int(startDateLabel.length()), 7);
	std::getline(std::cin, startDate);

	gotoXY(int(endDateLabel.length()), 8);
	std::getline(std::cin, endDate);

	gotoXY(int(vehicleTypeLabel.length()), 9);
	std::cin >> vehicleType;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	auto freeVehicles = this->db->getVehicle(Date(startDate), Date(endDate), VehicleType(vehicleType));

	if (freeVehicles.size() == 0)
	{
		this->showDialog("No vehicles are free in given date range");
		return;
	}
	gotoXY(0, 12);
	std::cout << "|Registration no  |" << "Seats  |" << "Price per km  |" << std::endl;

	for (auto& vehicle : freeVehicles)
	{
		std::string registrationNo = vehicle->getRegistrationNumber();
		std::string seats = std::to_string(vehicle->getSeats());

		std::stringstream ss;
		ss << std::fixed;
		ss << std::setprecision(2);
		ss << vehicle->getPricePerKm();

		std::string price = ss.str() + "Rs/Km";

		std::cout << "|" << registrationNo << std::string(7, ' ') << "|" << seats << std::string(7 - seats.length(), ' ') << "|" << price << std::string(14 - price.length(), ' ') << "|" << std::endl;
	}
	int offset = int(freeVehicles.size()) + 2;

	gotoXY(0, 12 + offset);
	std::cout << registrationNoLabel;

	gotoXY(int(registrationNoLabel.length()), 12 + offset);
	std::getline(std::cin, registrationNo);

	try
	{
		vehicle = this->db->getVehicle(registrationNo);
	}
	catch (Error e)
	{
		this->showDialog(e.getMessage());
		return;
	}
	long userId = user->getRecordId();
	long vehicleId = vehicle->getRecordId();

	Trip * trip;
	try
	{
		trip = new Trip(this->db->getVehicleRef()->getRecordForId(vehicleId), this->db->getUserRef()->getRecordForId(userId), Date(startDate), Date(endDate));
		this->db->addNewRecord(trip);
		std::stringstream ss;
		ss << "Trip Id : " << trip->getRecordId();
		showDialog("Trip added successfully", ss.str());
	}
	catch (Error e)
	{
		showDialog(e.getMessage());
	}
	delete trip;

}

void Application::renderViewTripMenu() const
{
	std::string header = "Enter trip id : ";
	
	long tripId;
	
	system("cls");

	gotoXY(0, 1);
	std::cout << header;

	gotoXY(int(header.length()), 1);
	std::cin >> tripId;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	gotoXY(0, 3);
	try
	{
		auto trip = this->db->getTripRef()->getRecordForId(tripId);
		trip->display();

		std::cout << std::endl << "Press any key to continue";
		std::cin.get();
	}
	catch (Error e)
	{
		this->showDialog(e.getMessage());
	}
}

void Application::renderStartTripMenu() const
{
	std::string header = "Enter trip id : ";
	std::string readingLabel = "Enter odometer reading : ";

	long tripId;
	long startReading;

	system("cls");

	gotoXY(0, 1);
	std::cout << header;

	gotoXY(0, 2);
	std::cout << readingLabel;

	gotoXY(int(header.length()), 1);
	std::cin >> tripId;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	gotoXY(int(readingLabel.length()), 2);
	std::cin >> startReading;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	Trip * modifiedTrip;

	try
	{
		auto trip = this->db->getTripRef()->getRecordForId(tripId);
		modifiedTrip = new Trip(*trip);
		modifiedTrip->startTrip(startReading);

		this->db->updateRecord(modifiedTrip);
		showDialog("Trip started successfully");
	}
	catch (Error e)
	{
		this->showDialog(e.getMessage());
	}
	delete modifiedTrip;
}

void Application::renderCompleteTripMenu() const
{
	std::string header = "Enter trip id : ";
	std::string readingLabel = "Enter odometer reading : ";

	long tripId;
	long endReading;

	system("cls");

	gotoXY(0, 1);
	std::cout << header;

	gotoXY(0, 2);
	std::cout << readingLabel;

	gotoXY(int(header.length()), 1);
	std::cin >> tripId;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	gotoXY(int(readingLabel.length()), 2);
	std::cin >> endReading;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	try
	{
		auto trip = this->db->getTripRef()->getRecordForId(tripId);
		Trip * modifiedtrip = new Trip(*trip);
		auto fare = modifiedtrip->completeTrip(endReading);
		this->db->updateRecord(modifiedtrip);

		std::stringstream ss;
		ss << "Total fare : " << fare;
		showDialog("Trip completed successfully", ss.str());
	}
	catch (Error e)
	{
		this->showDialog(e.getMessage());
	}

}

void Application::showDialog(std::string message, std::string id) const
{
	auto messageLength = int(message.length());

	std::string pressAnyKey = "Press any key to continue";
	int infoLength = int(pressAnyKey.length());

	int leftOffset = 15;
	int length = 50;
	int lineOffset = 9;

	system("cls");

	// line 1
	gotoXY(leftOffset, lineOffset++);
	std::cout << "**************************************************";

	// line 2
	gotoXY(leftOffset, lineOffset);
	std::cout << "*";
	gotoXY(leftOffset + length - 1, lineOffset++);
	std::cout << "*";

	// line 3
	gotoXY(leftOffset, lineOffset);
	std::cout << "*";
	gotoXY((80 - messageLength) / 2, lineOffset);
	std::cout << message;
	gotoXY(leftOffset + length - 1, lineOffset++);
	std::cout << "*";

	if (id != "")
	{
		// line 4
		gotoXY(leftOffset, lineOffset);
		std::cout << "*";
		gotoXY((int)((80 - int(id.length())) / 2), lineOffset);
		std::cout << id;
		gotoXY(leftOffset + length - 1, lineOffset++);
		std::cout << "*";
	}

	// line 5
	gotoXY(leftOffset, lineOffset);
	std::cout << "*";
	gotoXY((int)((80 - infoLength) / 2), lineOffset);
	std::cout << pressAnyKey;
	gotoXY(leftOffset + length - 1, lineOffset++);
	std::cout << "*";

	// line 6
	gotoXY(leftOffset, lineOffset);
	std::cout << "*";
	gotoXY(leftOffset + length - 1, lineOffset++);
	std::cout << "*";

	// line 7
	gotoXY(leftOffset, lineOffset++);
	std::cout << "**************************************************";
	std::cin.get();

	system("cls");
}

void Application::welcome()
{
	system("cls");
	gotoXY(25, 5);
	std::cout << "Welcome to Vehicle Rental System" << std::endl;
	gotoXY(27, 23);
	std::cout << "Press any key to continue";

	std::cin.get();

	this->renderMenu();
}

void Application::start()
{
	welcome();
}

void Application::cleanMemory()
{
	delete db;	
}