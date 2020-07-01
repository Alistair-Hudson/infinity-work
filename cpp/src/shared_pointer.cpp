/******************************************************************************
 *	Title:		Shared Pointer
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	01.07.2020.0
 ******************************************************************************/

#include "shared_pointer.hpp"

/******MACROS******/

/******TYPEDEFS*****/

/****** GLOBAL VARIABLES*****/

/*****STRUCTS*******/
struct Test
{
  int m_i;  
};

struct DerivedTest : public Test
{
    char m_c;
};

/*****CLASSES******/

/******CLASS FUNCTIONS*******/
template<typename T>
SharedPointer<T>::SharedPointer(T *m_ptr): m_pointer(new T)
{
    m_pointer = m_ptr;
    counter = new int(1);
}

template<typename T>
SharedPointer<T>::SharedPointer(const SharedPointer<T> &other_): m_pointer(other_.m_pointer)
{
    ++*counter;
}

template<typename T>
SharedPointer<T>::~SharedPointer()
{
    --*counter;
    if(0 == *counter)
    {
        delete m_pointer;
        delete counter;
    }
}

template<typename T>
SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer<T>& other)
{
    if ( this == &other || m_pointer == other.m_pointer)
    {
        return *this;
    }
    --*counter;
    if (0 == *counter)
    {
        delete m_pointer;
        delete counter;
    }
    m_pointer = other.m_pointer;
    ++*counter;
    return *this;
}

template <typename T>
template <typename C> // Used for upcasting
SharedPointer<T>::SharedPointer(const SharedPointer<C> &other_)
{
    m_pointer = &(*other_);
    counter = new int(1);
}

template <typename T>
template <typename C> // Used for upcasting
SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer<C> &other)
{
    --*counter;
    if (0 == *counter)
    {
        delete m_pointer;
        delete counter;
    }
    m_pointer = &(*other);
    counter = new int(1);
    return *this;
}

template<typename T>
T* SharedPointer<T>::operator->() const // can be applied on both const and not const obj
{
    return m_pointer;
}

template<typename T>
T& SharedPointer<T>::operator*() const
{
    return *m_pointer;
}

/******INTERNAL FUNCTION DECLARATION******/

/*****FUNCTION DEFINITION******/

int main()
{
    SharedPointer<int> i(new int(10));
    SharedPointer<Test> t(new Test);
    
    SharedPointer<DerivedTest> dt(new DerivedTest);
    
    *i = 50;
    t->m_i = 10;
    dt->m_i = 5;
    dt->m_c = 'C';
    
    std::cout << *i << std::endl;
    std::cout << t->m_i << std::endl;
    std::cout << dt->m_i << " " << dt->m_c << std::endl;
    
    SharedPointer<Test> conversion(new Test);
    conversion = dt;
    std::cout << conversion->m_i << std::endl;
    SharedPointer<Test> conversion2(dt);
    std::cout << conversion2->m_i << std::endl;
/*    
    SharedPointer<DerivedTest> con2(new DerivedTest);
    con2  = t;
    std::cout << con2->m_i << std::endl;
*/   
    return 0;
}