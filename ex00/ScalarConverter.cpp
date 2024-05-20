#include "ScalarConverter.hpp"
#include <cctype>
#include <exception>
#include <cstdlib>
#include <errno.h>
#include <cmath>
#include <limits>
#include <limits.h>

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

int isNone(const std::string &str)
{
    int dots_count = 0;
    int f_count = 0;
    std::string::const_iterator it = str.begin();
    if(str.length() > 1)
    {
        for(std::string::const_iterator it2 = str.begin(); it2 != str.end(); it2++)
        {
            if(*it2 == '.' && !std::isdigit(*(it2 + 1)))
                return(0);
            if(*it2 == '.' || *it2 == 'f')
                continue;
            else if(!std::isdigit(*it2) &&  it2 != it)
                return(0);
        }
    }
    else if(!std::isdigit(*it))
        return(1);
    else 
        return(2);
    while(it++ != str.end())
    {
        if(*it == '.')
            dots_count++;
        else if(*it == 'f')
            f_count++;
    }
    if(dots_count > 1 || f_count > 1)
        return (0);
    if(str.find('f', 0) != std::string::npos)
        return(3);
    else if(str.find('.', 0) != std::string::npos)
        return(4);
    return(2);
}

void printErr(void)
{
    std::cerr << "Error, format is incorrect" << std::endl;
}

void printChar(const char *s, int i, double number, int imp);
void printInt(const char *s, int i, double number, int imp);
void printFloat(const char *s, int i, double number, int imp);

void printDouble(const char *s, int i, double number, int imp)
{
    if(i == 0)
    {
        double c = std::strtod(s, NULL);
        if(errno == ERANGE || c > std::numeric_limits<double>::max() || c < (std::numeric_limits<double>::max() *-1))
        {
            imp = 1;
            printChar(s, 1, number, imp);
            printInt(s, 1, number, imp);
            printFloat(s, 1, number, imp);
            std::cout << "double: impossible" << std::endl;
        }
        else
        {
            int check = static_cast<int>(c);
            printChar(s, 1, c, imp);
            printInt(s, 1, c, imp);
            printFloat(s, 1, c, imp);
            if(c - check > 0)
                std::cout << "double: " << c << std::endl;
            else
                std::cout << "double: " << c << ".0" << std::endl;
        }
    }
    else
    {
        if(imp)
            std::cout << "double: impossible" << std::endl;
        else
        {
            double c = static_cast<double>(number);
            if(c > std::numeric_limits<double>::max() || c < (std::numeric_limits<double>::max() *-1))
                imp = 1;
            int check = static_cast<int>(number);
            if(imp == 1)
                std::cout << "double: impossible" << std::endl;
            else if(c - check > 0)
                std::cout << "double: " << c << std::endl;
            else
                std::cout << "double: " << c << ".0" << std::endl;
        }
    }
    return;
}

void printFloat(const char *s, int i, double number, int imp)
{
    if(i == 0)
    {
        double numd = std::strtod(s, NULL);
        if(errno == ERANGE || numd > std::numeric_limits<float>::max() || numd < (std::numeric_limits<float>::max() *-1))
        {
            imp = 1;
            printChar(s, 1, number, imp);
            printInt(s, 1, number, imp);
            std::cout << "float: impossible" << std::endl;
            printDouble(s, 1, number, imp);
        }
        else
        {
            float c = static_cast<float>(numd);
            int check = static_cast<int>(numd);
            printChar(s, 1, numd, imp);
            printInt(s, 1, numd, imp);
            if(imp == 1)
                std::cout << "float: impossible" << std::endl;
            else if(c - check > 0)
                std::cout << "float: " << c << "f" << std::endl;
            else
                std::cout << "float: " << c << ".0f" << std::endl;
            printDouble(s, 1, numd, imp);
        }
    }
    else
    {
        if(imp)
            std::cout << "float: impossible" << std::endl;
        else
        {
            float c = static_cast<float>(number);
            if(c > std::numeric_limits<float>::max() || c < (std::numeric_limits<float>::max() *-1))
                imp = 1;
            int check = static_cast<int>(number);
            if(imp == 1)
                std::cout << "float: impossible" << std::endl;
            else if(c - check > 0)
                std::cout << "float: " << c << "f" << std::endl;
            else
                std::cout << "float: " << c << ".0f" << std::endl;
        }
    }
    return;
}

void printInt(const char *s, int i, double number, int imp)
{
    if(i == 0)
    {
        long int numd = std::strtol(s, NULL, 10);
        if(errno == ERANGE || (numd < INT_MIN || numd > INT_MAX))
        {
            imp = 1;
            printChar(s, 1, number, imp);
            std::cout << "int: impossible" << std::endl;
            number = std::strtod(s, NULL);
            if(errno == ERANGE || number > std::numeric_limits<float>::max() || number < (std::numeric_limits<float>::max() *-1))
                imp = 1;
            else
                imp = 0;
            printFloat(s, 1, number, imp);
            number = std::strtod(s, NULL);
            if(number > std::numeric_limits<double>::max() || number < (std::numeric_limits<double>::max() *-1))
                imp = 1;
            else
                imp = 0;
            printDouble(s, 1, number, imp);
        }
        else
        {
            int c = static_cast<int>(numd);
            printChar(s, 1, static_cast<double>(c), imp);
            std::cout << "int: " << c << std::endl;
            printFloat(s, 1, static_cast<double>(c), imp);
            printDouble(s, 1, static_cast<double>(c), imp);
        }
    }
    else
    {
        long int num = std::strtol(s, NULL, 10);
        if(errno == ERANGE || num > INT_MAX || num < INT_MIN)
                imp = 1;
        if(imp)
            std::cout << "int: impossible" << std::endl;
        else
        {
            
            int c = static_cast<int>(number);
            std::cout << "int: " << c << std::endl;
        }
    }
    return;
}

void printChar(const char *s, int i, double number, int imp)
{
    if(imp)
    {
        std::cout << "char: impossible" << std::endl;
        return;
    }
    if(i == 0)
    {
        char c = static_cast<char>(s[0]);
        if(std::isprint(c))
            std::cout << "char: '" << c << "'" << std::endl;
        else
            std::cout << "char: Non displayable" << std::endl;
        double numd = static_cast<double>(c);
        printInt(s, 1, numd, imp);
        printFloat(s, 1, numd, imp);
        printDouble(s, 1, numd, imp);
    }
    else
    {
        char c = static_cast<char>(number);
        if(imp || number < 0 || number > 255)
            std::cout << "char: impossible" << std::endl;
        else
        {
            if(std::isprint(c))
                std::cout << "char: '" << c << "'" << std::endl;
            else
                std::cout << "char: Non displayable" << std::endl;
        }
    }
    return;
}

void ScalarConverter::convert(const std::string &str)
{
    if(ScalarConverter::isPseudoLiteral(str))
        return ;

    int type = isNone(str);

    switch (type)
    {
        case 1:
            printChar(str.c_str(), 0, 0, 0);
            break;

        case 2:
            printInt(str.c_str(), 0, 0, 0);
            break;

        case 3:
            printFloat(str.c_str(), 0, 0, 0);
            break;

        case 4:
            printDouble(str.c_str(), 0, 0, 0);
            break;

        default:
            return(printErr());
    }
}
