#include "ScalarConverter.hpp"
#include <cctype>
#include <exception>
#include <cstdlib>

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
                return(1);
            if(*it2 == '.' || *it2 == 'f')
                continue;
            else if(!std::isdigit(*it2) &&  it2 != it)
                return(1);
        }
    }
    else if(!std::isdigit(*it))
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
    double numd = std::atof(str.c_str());
    char c = static_cast<char>(numd);
    if(std::isprint(c))
        std::cout << "char: '" << c << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;
    int numi = static_cast<int>(numd);
    std::cout << "int: " << numi << std::endl;
    if(numd - numi != 0)
    {
        std::cout << "float: " << numd << "f" << std::endl;
        std::cout << "double: " << numd << std::endl;
    }
    else
    {
        std::cout << "float: " << numd << ".0f" << std::endl;
        std::cout << "double: " << numd <<  ".0" << std::endl;
    }
}
