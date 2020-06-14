/******************************************************************************
 *	Title:		Histo
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	14.06.2020.0
 ******************************************************************************/

#include <iostream>
#include <queue>
#include <vector>
#include <string.h>

/******MACROS******/

/******TYPEDEFS*****/

/*****STRUCTS*******/

/*****CLASSES******/
class String
{
public:
    String(char* str);
    
    inline const char* GetString() const;
    inline int GetCount() const;
    inline void IncreaseCount();

private:
    char m_str[100];
    int m_count;
};

/******CLASS FUNCTIONS*******/
String::String(char* str)
{
    strcpy(m_str, str);
    m_count = 1;
}

const char* String::GetString() const
{
    return m_str;
}

int String::GetCount() const
{
    return m_count;
}

void String::IncreaseCount()
{
    ++m_count;
}

/****** GLOBAL VARIABLES*****/

/******INTERNAL FUNCTION DECLARATION******/
template <typename T>
void StackQue(std::queue<T>* que);
template <typename T>
std::vector<String> DequeAndCount(std::queue<T>* que);
void PrintOut(std::vector<String>* list);

/*****FUNCTION DEFINITION******/
int main()
{
    std::queue<char*> string_q;
    
    StackQue(&string_q);
    
    std::vector<String> list = DequeAndCount(&string_q);
    
    PrintOut(&list);
    
   
    
    return 0;
}

template <typename T>
void StackQue(std::queue<T>* que)
{
    std::cout << "PLease enter strings\n" 
                << "press ESC followed by Enter to exit" << std::endl;
    while(1)
    {
        char *str = new char[100];
        std::cin>> str;
        if (27 == *str)
        {
            return;
        }
        que->push(str);
    }
}

template <typename T>
std::vector<String> DequeAndCount(std::queue<T>* que)
{
    std::vector<String> list;
    
    while (!que->empty())
    {
        int i = 0;
        while (i < list.size())
        {
            if (!strcmp(que->front(), list.at(i).GetString()))
            {
                list.at(i).IncreaseCount();
                break;
            }
            ++i;
        }
        if (i == list.size())
        {
            list.push_back(que->front());
        }
        que->pop();
    }
    
    return list;
}

void PrintOut(std::vector<String>* list)
{
    int i = 0;
    std::cout << "Histogram:" << std::endl;
    while(i < list->size())
    {
        std::cout << list->at(i).GetString() << " x" 
                    << list->at(i).GetCount() << std::endl;
                    
        ++i;
    }
}