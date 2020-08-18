/*******************************************************************************
 * File: Minion API                                
 * Author: Alistair Hudson
 * Reviewed by:                       
 * Date: 06.08.2020.0                                                                
 ******************************************************************************/
#ifndef __ILRD_RD8586_MINION_HPP__
#define __ILRD_RD8586_MINION_HPP__

#include <boost/noncopyable.hpp> // boost::noncopyable

#include "protocol.hpp"
#include "reactor_w_callback.hpp"
#include "mastercommunicator.hpp"
#include "storage.hpp"
#include "logger.hpp"

namespace ilrd
{
class Minion: private boost::noncopyable
{
public:

    explicit Minion(int port, int num_of_blocks, int master_port);
    ~Minion();

    // Run
    // Receives: nothing
    // Returns: nothing
    void Run();

private:
    // OnRequest
    // Receives: Request structure.
    // Returns: nothing
    void OnRequest(const Request& request);

    Reactor m_reactor;
    MasterCommunicator m_comm;
    Storage<G_BLOCK_SIZE> m_storage;
    Response m_response;
};

} // namespace ilrd

#endif /* __ILRD_RD8586_Minion_HPP__ */