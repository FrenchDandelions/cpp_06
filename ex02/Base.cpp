#include "Base.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Base::~Base()
{
}
Base *generate(void){
    static bool initialized = false;
    if (!initialized) {
        std::srand(std::time(NULL));
        initialized = true;
    }
    int i = std::rand() % 3;
    switch (i)
    {
        case 1:
            return (new B);

        case 2:
            return (new C);

        default:
            return (new A);
    }
    return(NULL);
}

void identify(Base *p)
{
    A* a = dynamic_cast<A*>(p);
    if(a == NULL)
    {
        B* b = dynamic_cast<B*>(p);
        if(b == NULL)
        {
            C* c = dynamic_cast<C*>(p);
            if(c == NULL)
            {
                std::cout << "It's either an unknown type or a Base pointer!" << std::endl;
            }
            else
            {
                std::cout << "It's a type C! (Found in the identify pointer function)" << std::endl;
            }
        }
        else
        {
            std::cout << "It's a type B! (Found in the identify pointer function)" << std::endl;
        }
    }
    else
    {
        std::cout << "It's a type A! (Found in the identify pointer function)" << std::endl;
    }
}

void identify(Base &p)
{
    try
    {
        A& a = dynamic_cast<A&>(p);
        (void)a;
        std::cout << "It's a type A! (Found in the identify ref function)" << std::endl;
        return;
    }
    catch(std::exception& e){}
    try
    {
        B& b = dynamic_cast<B&>(p);
        (void)b;
        std::cout << "It's a type B! (Found in the identify ref function)" << std::endl;
        return;
    }
    catch(std::exception& e){}
    try
    {
        C& c = dynamic_cast<C&>(p);
        (void)c;
        std::cout << "It's a type C! (Found in the identify ref function)" << std::endl;
        return;
    }
    catch(std::exception& e)
    {
        std::cout << "It's either an unknown type or a Base pointer!" << std::endl;
    }
}
