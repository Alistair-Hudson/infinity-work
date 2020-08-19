#include <iostream>
#include <cstring>

#include "storage.hpp"
#include "protocol.hpp"
#include "command.hpp"
#include "factory.hpp"
using namespace ilrd;

int main()
{
    Storage < G_BLOCK_SIZE > storage1(100);
    Factory<int, BaseCommand,Params,  BaseCommand* (*)(Params)> fact;
    Response response;
    Request request;
    char * str = "Hello";
    
    request.m_mode = 0;
    request.m_uid = 12345;
    request.m_index = 1;
    std::memcpy(request.m_data, str, sizeof(str));

    Params par = {storage1, response, request};

    fact.Add(1, WriteBuilder);
    fact.Add(0, ReadBuilder);
    (*(fact.Create(1, par)))();
    return(0);
}

