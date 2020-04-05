#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>
#include <memory>

class Person
{
public:
    Person(const std::string& name, int age,
           const std::string& addres);
    virtual ~Person();

    class PersonImpl;
    std::shared_ptr<PersonImpl> Impl;
    const std::string& GetName();
    const int GetAge();
    const std::string& GetAddress();
private:
    std::string _name;
    int _age;
    std::string _address;
};

#endif // PERSON_H
