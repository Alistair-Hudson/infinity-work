/******************************************************************************
 *	Title:		Scope Lock
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	01.07.2020.1
 ******************************************************************************/

#include "scope_lock.hpp"


/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****STRUCTS*******/

/*****CLASSES******/

/******CLASS FUNCTIONS*******/
template <typename Container>
irld::ScopeLock<Container>::ScopeLock(Container& container):m_c(container)
{
    m_c.lock();
}

template <typename Conatainer>
irld::ScopeLock<Conatainer>::~ScopeLock()
{
    m_c.unlock();
}

/******INTERNAL FUNCTION DECLARATION******/

/******FUNCTIONS*******/









