#ifndef ILRD_RD8586_COMMAND_HPP
#define ILRD_RD8586_COMMAND_HPP
/******************************************************************************
 * API COMMAND
 * Alistair Hudson
 * version 04.08.2020.0
******************************************************************************/

#include "protocol.hpp"
#include "storage.hpp"
#include "logger.hpp"

namespace ilrd
{

class BaseCommand
{
public:
    BaseCommand(){};
    virtual ~BaseCommand() {};
    virtual void operator()() = 0;
};

struct Params
{
    Storage<G_BLOCK_SIZE>& m_storage;
    Response& m_response;
    const Request& m_request;
};

class WriteCommand : public BaseCommand
{
public:
    WriteCommand(Params params): m_params(params){};
    ~WriteCommand() {};
    void operator()();

private:
    Params m_params;
};

class ReadCommand : public BaseCommand
{
public:
    ReadCommand(Params params):m_params(params){};
    ~ReadCommand() {};
    void operator()();
private:
    Params m_params;
};

//BUILDERS

 BaseCommand* WriteBuilder(Params m_params);
 BaseCommand* ReadBuilder(Params m_params);

}

#endif //ILRD_RD8586_COMMAND_HPP