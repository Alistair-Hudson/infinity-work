#include "storage.hpp"

int main()
{
    ilrd::Storage<8> store(10);
    char str[] = "string";

    std::cout << "capacity =" << store.GetCapacity() << std::endl;

    store.Write(3, str);

    char dest[8];

    store.Read(0, dest);
    std::cout << dest << std::endl;

    store.Read(3, dest);
    std::cout << dest << std::endl;


    return 0;
}