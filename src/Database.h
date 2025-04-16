#ifndef database_h
#define database_h

#include "Vehicle.h"
#include "User.h"
#include "Trip.h"
#include "Table.h"
#include "Error.cpp"

class Database
{
private:
    Table<Vehicle> * vehicleTable;

    Table<User> * userTable;

    Table<Trip> * tripTable;

	void fetchAllVehicles() throw(IOError, MemoryError);
	void fetchAllUsers()    throw(IOError, MemoryError);
	void fetchAllTrips()    throw(IOError, MemoryError);

    void cleanUp();
public:

    Database() throw(MemoryError, IOError);

    ~Database();

    const Table<Vehicle> * const getVehicleRef() const;

    const Table<User> * const getUserRef() const;

    const Table<Trip> * const getTripRef() const;

    const Vehicle * const getVehicle(std::string registrationNo) const throw(NoSuchRecordError);

    const User * const getUser(std::string contactNo) const throw(NoSuchRecordError);

    const std::vector<const Vehicle *> getVehicle(Date startDate, Date endDate, VehicleType type) const;

    template <class T> void addNewRecord(T * record) throw(IOError, MemoryError);

    template <class T> void updateRecord(T * record) throw(IOError, NoSuchRecordError);
};


#endif