/*******************************************************************************
 * File: prtocol.hpp - header for protocols for request and responce                                
 * Author: Yurii Yashchuk                                                          
 * Reviewed by:                       
 * Date: 05.08.2020.1                                                                
 ******************************************************************************/
#ifndef __ILRD_RD8586_MINION_PROTOCOL_HPP__
#define __ILRD_RD8586_MINION_PROTOCOL_HPP__

#include <stdlib.h>     /*  size_t */
#include <stdint.h>    /* unint_64_t */

#define BLOCK_SIZE (4096)

namespace ilrd
{
    struct Request
    {
        inline size_t RequestSize() const {return sizeof(*this);}

        uint64_t m_uid;
        uint64_t m_index;
        char m_mode;
        char m_data[BLOCK_SIZE];
    };

    struct Response
    {
        inline size_t ResponseSize() const {return sizeof(*this);}

        uint64_t m_uid;
        char m_mode;
        char m_status;
        char m_data[BLOCK_SIZE];
    };

} // namespace ilrd

#endif /* __ILRD_RD8586_STORAGE_HPP__ */