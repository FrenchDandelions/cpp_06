#include "Serializer.hpp"

int main()
{
    Data *data = new Data;
    std::cout << "Address before serialization and deserialization: " << data << std::endl;
    std::cout << "Address after serialization and deserialization: " << Serializer::deserialize(Serializer::serialize(data)) << std::endl;
    delete data;
}