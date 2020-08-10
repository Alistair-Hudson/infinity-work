#ifndef ILRD_RD8586_STORAGE_HPP
#define ILRD_RD8586_STORAGE_HPP
/******************************************************************************
 * API STORAGE
 * Alistair Hudson
 * version 04.08.2020.0
******************************************************************************/
#include <fstream>  //std::fstream
#include <assert.h> //assert

#include "boost/core/noncopyable.hpp"

namespace ilrd
{
template <size_t BLOCK_SIZE>
class Storage:private boost::noncopyable
{
public:
    // Possible return status: 0 == SUCCESS, 1 == FAILED TO OPEN, 2 == FAILED TO READ/WRITE, 3 == OUT OF RANGE 
    explicit Storage(size_t num_of_blocks);
    // Write Function
    // Receives: index where to write data, pointer to source.
    // Returns: status of operation        
    char Write(size_t index, const void *src);
    // Read Function
    // Receives: index from where to read, pointer to store read data .
    // Returns: status of operation
    char Read(size_t index, void * dest) const;

    // GetCapacity Function
    // Receives: nothing.
    // Return: size_t number of blocks     
    size_t GetCapacity() const { return m_capacity; }
private:
    size_t m_capacity;
    const char* m_name;    
};

template< size_t BLOCK_SIZE>
Storage<BLOCK_SIZE>::Storage(size_t num_of_blocks): m_capacity(num_of_blocks),
                                                    m_name("tardis.txt")
{
    //ensure that the file for storing data is created
    std::ofstream fs;
    fs.open(m_name);
    fs.close();
}

template< size_t BLOCK_SIZE>
char Storage<BLOCK_SIZE>::Write(size_t index, const void *src)
{
    //assert(m_capacity > index);

    std::fstream fs;
    fs.open(m_name);
    //if (!fs.is_open()){return 1;}

    fs.seekp(index * BLOCK_SIZE, std::ios::beg);
    fs.write((const char*)(src), BLOCK_SIZE);
    fs.close();
    std::cout << "wrote to storage\n";
    return 0;
}

template< size_t BLOCK_SIZE>
char Storage<BLOCK_SIZE>::Read(size_t index, void* dest)const
{
    //assert(m_capacity > index);
    
    std::fstream fs;
    fs.open(m_name);
    //if (!fs.is_open()){return 1;}

    fs.seekg(index * BLOCK_SIZE, std::ios::beg);
    fs.read(static_cast<char*>(dest), BLOCK_SIZE);
    fs.close();
    std::cout << "read from storage\n";
    return 0;
}

} // namespace ilrd

#endif // ILRD_RD8586_STORAGE_HPP  