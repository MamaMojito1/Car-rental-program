#ifndef users_h
#define users_h

#include "storable.cpp"

#include <string>

class User : public Storable
{
private:
    std::string name;

    std::string contact;

    std::string email;

public:

    User(std::string name, std::string contact, std::string email, long recordId = 0);

    std::string getName() const;

    std::string getContact() const;

    std::string getEmail() const;

    void setName(std::string newName);

    void setContact(std::string contact);

    void setEmail(std::string email);

    void display() const;

    std::string toString() const;

    void setDataFrom(Storable *s);
};

#endif