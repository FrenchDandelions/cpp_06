#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <iostream>

class Data
{
    private:
        int _value;
        std::string _str;
    public:
        Data();
        Data(int value, std::string str);
        Data(const Data &copy);
        Data& operator= (const Data &copy);
        ~Data();
};

#endif