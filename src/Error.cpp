#ifndef error_cpp
#define error_cpp

#include <string>

class Error
{
private:
    std::string message;
public:
    Error(std::string message) { this->message = message; }
    std::string getMessage() const { return this->message; }
};

class NoSuchRecordError : public Error
{
public:
    NoSuchRecordError() : Error("No such record found.") {};
};

class IOError : public Error
{
public:
    IOError() : Error("I/O error could not open or process file make sure 'vehicles.txt', 'trips.txt' and 'users.txt' file exists in this directory") {};
};

class MemoryError : public Error
{
public:
    MemoryError() : Error("System out of memory") {};
};

#endif