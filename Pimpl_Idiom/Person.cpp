#include "Person.h"


class Person::PersonImpl
{
public:
    const std::string& GetName(Person* person);
    const int GetAge(Person* person);
    const std::string& GetAddress(Person* person);
};

const std::string& Person::PersonImpl::GetName(Person* person)
{
    std::cout << "Here we can move some secret implementation, that "
                 "can't be seen by provided api !" << std::endl;
    return person->_name;
}

const int Person::PersonImpl::GetAge(Person* person)
{
    // some secret implementation
    if(person->_age > 18)
        std::cout << "The person is adult ... !" << std::endl;
    else
        std::cout << "The person is a child ... !" << std::endl;
    return person->_age;
}

const std::string& Person::PersonImpl::GetAddress(Person* person)
{
    std::cout << "Here we can move some secret implementation, that "
                 "can't be seen by provided api !" << std::endl;
    return person->_address;
}

Person::Person(const std::string& name, int age, const std::string& address)
    :Impl(std::make_shared<PersonImpl>()),
      _name(name),
      _age(age),
      _address(address)
{
}

Person::~Person()
{
    // Impl is a smart ptr and not need to be deleted
}

const std::string& Person::GetName()
{
    Impl->GetName(this);
}

const int Person::GetAge()
{
    Impl->GetAge(this);
}

const std::string& Person::GetAddress()
{
    Impl->GetAddress(this);
}
