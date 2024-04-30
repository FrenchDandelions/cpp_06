#include "ScalarConverter.hpp"
#include <sstream>
#include <cctype>

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
    return(*this);
}

ScalarConverter::~ScalarConverter()
{
}

// int isChar(const std::string &str)
// {
//     int i = 0;
//     int points = 0;
// }

void printPseudoLit(const std::string &str)
{
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    if(str.find('f', 0) != std::string::npos && (str.length() > 4 || *str.begin() == 'n'))
    {
        std::cout << "float: " << str << std::endl;
        std::cout << "double: " << str.substr(0, str.length() - 1)<< std::endl;
    }
    else
    {
        std::cout << "float: " << str + "f" << std::endl;
        std::cout << "double: " << str << std::endl;
    }

}

int ScalarConverter::isPseudoLiteral(const std::string &str)
{
    std::string tab [6] = {"+inff", "-inff", "nan", "nanf", "-inf", "+inf"};
    for(int i = 0; i < 6; i++)
    {
        if(tab[i] == str)
            return(printPseudoLit(tab[i]), 1);
    }
    return(0);
}


// void printChar(const std::string &str)
// {

// }

// void printInt(const std::string &str)
// {
    
// }

// void printFloat(const std::string &str)
// {
    
// }

// void printDouble(const std::string &str)
// {
    
// }

int isNone(const std::string &str)
{
    int dots_count = 0;
    int f_count = 0;
    std::string::const_iterator it = str.begin();
    if(str.length() > 1 && !std::isdigit(str[1]))
        return(1);
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

void printErr(void)
{
    std::cerr << "Error, format is incorrect" << std::endl;
}

void ScalarConverter::convert(const std::string &str)
{
    if(ScalarConverter::isPseudoLiteral(str))
        return ;
    if(isNone(str))
        return(printErr());
    std::stringstream ss;
    ss << str;
    int number;
    ss >> number;
    std::cout << number << std::endl;
    float fnumber = static_cast<float>(number);
    std::cout << fnumber << std::endl;
    // printChar(str);
    // printInt(str);
    // printFloat(str);
    // printDouble(str);
}
