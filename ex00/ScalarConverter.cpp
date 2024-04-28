#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::ScalarConverter(const ScalarConverter &copy)
{
    (void)copy;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter &copy)
{
    (void)copy;
}

ScalarConverter::~ScalarConverter()
{
}

int isChar(const std::string &str)
{
    int i = 0;
    int points = 0;
}

int ScalarConverter::isPseudoLiteral(const std::string &str)
{
    if(str == "+inff" || str == "-inff" || str == "nan" || str == "-inf" || str == "+inf")
        return(1);
    return(0);
}

void printPseudoLit(const std::string &str)
{
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    std::cout << "float: impossible" << std::endl;
    std::cout << "double: impossible" << std::endl;
}

void printChar(const std::string &str)
{

}

void printInt(const std::string &str)
{
    
}

void printFloat(const std::string &str)
{
    
}

void printDouble(const std::string &str)
{
    
}

int isNone(const std::string &str)
{
    int dots_count = 0;
    int f_count = 0;
    int i;
    std::string::const_iterator it = str.begin();
    while(it++ != str.end())
    {
        if(*it == '.')
            dots_count++;
        else if(*it == 'f')
            f_count++;
    }
    if(dots_count > 1 || f_count > 1)
        return 1;
    return(0);
}

void printErr(const std::string &str)
{
    std::cerr << "Error, format is incorrect" << std::endl;
}

void ScalarConverter::convert(const std::string &str)
{
    if(ScalarConverter::isPseudoLiteral(str))
        return(printPseudoLit(str));
    if(isNone(str))
        return(printErr(str));
    printChar(str);
    printInt(str);
    printFloat(str);
    printDouble(str);
}
