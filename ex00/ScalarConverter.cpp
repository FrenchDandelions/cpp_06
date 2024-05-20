#include "ScalarConverter.hpp"
#include <cctype>
#include <cstdlib>
#include <errno.h>
#include <cmath>
#include <limits>
#include <limits.h>

void printChar(const char *s, int i, double number, int imp);
void printInt(const char *s, int i, double number, int imp);
void printFloat(const char *s, int i, double number, int imp);

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
        else if(c > std::numeric_limits<float>::max() || c < (std::numeric_limits<float>::max() *-1))
        {
            imp = 1;
            printChar(s, 1, number, imp);
            printInt(s, 1, number, imp);
            printFloat(s, 1, number, imp);
            std::cout << "double: " << c << std::endl;
        }
        else
        {
            float f = static_cast<float>(c);
            int check = static_cast<int>(c);
            char ch = static_cast<char>(c);
            if(check < 0 || check > 255)
                printChar(s, i, 0 ,1);
            else if(std::isprint(ch))
                std::cout << "char: '" << ch << "'" << std::endl;
            else
                std::cout << "char: Non displayable" << std::endl;
            long int nums = std::strtol(s, NULL, 10);
            if(nums > INT_MIN && nums < INT_MAX)
                std::cout << "int: " << check << std::endl;
            else
                std::cout << "int: impossible" << std::endl;
            std::cout << "float: " << f << "f" << std::endl;
            std::cout << "double: " << c << std::endl;
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
    if(imp)
    {
        std::cout << "float: impossible" << std::endl;
        return;
    }
    if(i == 0)
    {
        double numd = std::strtod(s, NULL);
        if((numd > std::numeric_limits<float>::max() || numd < (std::numeric_limits<float>::max() *-1)) && errno != ERANGE)
        {
            imp = 1;
            printChar(s, 1, number, imp);
            printInt(s, 1, number, imp);
            std::cout << "float: impossible" << std::endl;
            std::cout << "double: " << numd << std::endl;
        }
        else if (errno == ERANGE)
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
        else
        {
            float c = static_cast<float>(numd);
            int check = static_cast<int>(numd);
            char ch = static_cast<char>(numd);
            if(check < 0 || check > 255)
                printChar(s, i, 0 ,1);
            else if(std::isprint(ch))
                std::cout << "char: '" << ch << "'" << std::endl;
            else
                std::cout << "char: Non displayable" << std::endl;
            long int nums = std::strtol(s, NULL, 10);
            if(nums > INT_MIN && nums < INT_MAX)
                std::cout << "int: " << check << std::endl;
            else
                std::cout << "int: impossible" << std::endl;
            std::cout << "float: " << c << "f" << std::endl;
            std::cout << "double: " << numd << std::endl;
        }
    }
    return;
}

void printInt(const char *s, int i, double number, int imp)
{
    if(imp)
    {
        std::cout << "int: impossible" << std::endl;
        return;
    }
    (void)number;
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
                printFloat(s, i, number, imp);
            else
            {
                float numf = static_cast<float>(numd);
                std::cout << "float: " << numf << ".0f" << std::endl;
            }
            number = std::strtod(s, NULL);
            if(number > std::numeric_limits<double>::max() || number < (std::numeric_limits<double>::max() *-1))
                printDouble(s, 1, number, imp);
            else
            {
                number = static_cast<double>(numd);
                std::cout << "double: " << number << ".0" << std::endl;
            }
        }
        else
        {
            int c = static_cast<int>(numd);
            char ch = static_cast<char>(numd);
            float f = static_cast<float>(numd);
            number = static_cast<double>(numd);
            if(c < 0 || c > 255)
                printChar(s, i, 0 ,1);
            else if(std::isprint(ch))
                std::cout << "char: '" << ch << "'" << std::endl;
            else
                std::cout << "char: Non displayable" << std::endl;
            std::cout << "int: " << c << std::endl;
            std::cout << "float: " << f << ".0f" << std::endl;
            std::cout << "double: " << number << ".0" << std::endl;
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
    (void)number;
    if(i == 0)
    {
        char c = static_cast<char>(s[0]);
        if(std::isprint(c))
            std::cout << "char: '" << c << "'" << std::endl;
        else
            std::cout << "char: Non displayable" << std::endl;
        double numd = static_cast<double>(c);
        int num = static_cast<int>(c);
        int numf = static_cast<float>(c);
        std::cout << "int: " << num << std::endl;
        if(numf - num > 0)
        {
            std::cout << "float: " << numf << "f" << std::endl;
            std::cout << "double: " << numd << std::endl;
        }
        else
        {
            std::cout << "float: " << numf << ".0f" << std::endl;
            std::cout << "double: " << numd << ".0" << std::endl;
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
