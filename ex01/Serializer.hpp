#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

# include "Data.hpp"
# include <ctype.h>

class Serializer
{
    private:
        Serializer();
        Serializer(const Serializer &copy);
        Serializer& operator=(const Serializer &copy);

    public:
        ~Serializer();
        static uintptr_t serialize(Data *ptr);
        static Data* deserialize(uintptr_t raw);
};

#endif
