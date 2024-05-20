#include "ScalarConverter.hpp"

int main(int argc, char**argv)
{
    if(argc ==2)
    {
        std::string str = argv[1];
        ScalarConverter::convert(str);
    }
    else
        std::cerr << "Error, wrong argument count, it should be: "
        "./ScalarConverter arg" << std::endl;
}
