#include "User.h"
#include "string_helper.h"

#include <iostream>

const char DELIMITER = ';';

User::User(std::string name, std::string contact, std::string email, long recordId)
    : Storable(recordId)
{
    this->name = name;
    this->contact = contact;
    this->email = email;
}

std::string User::getName() const
{
    return this->name;
}

std::string User::getContact() const
{
    return this->contact;
}

std::string User::getEmail() const
{
    return this->email;
}

void User::setName(std::string newName)
{
    this->name = newName;
}

void User::setContact(std::string newContact)
{
    this->contact = newContact;
}

void User::setEmail(std::string newEmail)
{
    this->email = newEmail;
}

void User::display() const
{
    std::cout << "User details : " << std::endl;
    std::cout << "Name : " << this->name << std::endl;
    std::cout << "Contact : " << this->contact << std::endl;
    std::cout << "Email : " << this->email << std::endl;
}

std::string User::toString() const
{
    std::stringstream ss;
    ss << recordId << DELIMITER
       << name << DELIMITER
       << contact << DELIMITER
       << email;
    
    return ss.str();
}

void User::setDataFrom(Storable *s)
{
    User* user = dynamic_cast<User*>(s);
    
    if(user)
    {
        this->contact = user->contact;
        this->name = user->name;
        this->email = user->email;
    }
}