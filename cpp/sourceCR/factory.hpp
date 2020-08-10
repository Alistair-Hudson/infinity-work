#ifndef ILRD_RD8586_FACTORY_HPP
#define ILRD_RD8586_FACTORY_HPP


/******************************************************************************
 * API FACTORY
 * 02.08.2020
 * 
******************************************************************************/

#include <iostream>
#include <map>
#include "boost/core/noncopyable.hpp"

namespace ilrd
{
//Factory can be created as a singleton ,Shapes can be used for test
template<class KEY,class BASE,class PARAMS ,class BUILDER = BASE* (*)(PARAMS)>
class Factory:private boost::noncopyable
{
public:

    // Add Function
    // Receives: key - key to the specific function to be created.
    //           creation_func - function which creates a specific object.
    // Exceptions: throws runtime_error if function is NULL;
    // Throws run-time exception if key already exist
    // BUILDER accepts functions which follows this declaration BASE* (*) (PARAMS) 
     
    void Add(KEY key, BUILDER creation_func);

    // Create Function
    // Receives: key - key to the specific function to be created.
    //           build_params - params that are needed for a creation function.
    // Exceptions: throws runtime_error if creation fails or key doesn't exist.

    BASE* Create(KEY key, PARAMS build_params)const;
private:
    std::map<KEY, BUILDER>m_factory_creation;
};

template<class KEY,class BASE,class PARAMS ,class BUILDER>
void Factory<KEY, BASE, PARAMS, BUILDER >::Add(KEY key, BUILDER creation_func)
{
    if (NULL == creation_func)
    { 
        throw "Error: No creation function cannot build\n";
    }
    if (m_factory_creation.find(key) != m_factory_creation.end())
    {
        throw "Error: Creator already exists, cannot add\n";
    }

    m_factory_creation[key] = creation_func;
}

template<class KEY,class BASE,class PARAMS ,class BUILDER>
BASE* Factory<KEY, BASE, PARAMS, BUILDER >::Create(KEY key, PARAMS build_params)const
{
    typename std::map<KEY, BUILDER>::const_iterator iter;
    try
    {
        iter = m_factory_creation.find(key);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return iter->second(build_params);
}



} // namespace ilrd

#endif // ILRD_RD8586_FACTORY_HPP 