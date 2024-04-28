#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#include <string>
#include <iostream>

class ScalarConverter
{
    private:
        ScalarConverter();
        ScalarConverter(const ScalarConverter &copy);
        ScalarConverter& operator=(const ScalarConverter &copy);
        ~ScalarConverter();
        static int isPseudoLiteral(const std::string &str);

    public:
        static void convert(const std::string &string);
};

#endif
