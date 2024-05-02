#include "Base.hpp"

int main()
{
    Base *p = generate();
    identify(p);
    identify(*p);
    Base *p2 = generate();
    identify(p2);
    identify(*p2);
    delete p2;
    delete p;
}
