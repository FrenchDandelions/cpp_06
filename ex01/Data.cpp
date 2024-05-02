#include "Data.hpp"

Data::Data() : _value(42), _str("meaning of life")
{
}

Data::Data(int value, std::string str) : _value(value), _str(str)
{
}

Data::Data(const Data& copy) : _value(copy._value), _str(copy._str)
{

}

Data& Data::operator=(const Data& copy)
{
    if(this != &copy)
    {
        this->_value = copy._value;
        this->_str = copy._str;
    }
    return(*this);
}

Data::~Data()
{
}

