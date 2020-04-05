#include "Person.h"

int main(int argc, char *argv[])
{
    Person pObject("John Doe", 23, "Sofiq city, Lidice 13 str.");

    std::cout << "Name of person -> " << pObject.GetName() << std::endl;
    std::cout << "Age of person -> " << pObject.GetAge() << std::endl;
    std::cout << "Address of person -> " << pObject.GetAddress() << std::endl;
    return 0;
}
