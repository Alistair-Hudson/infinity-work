#include <iostream>
#include <list>
#include <iterator>
#include <string>

template<typename KEY, typename VALUE>
class GMap;

template <typename KEY, typename VALUE >
class MapPrinter
{
public:
    MapPrinter();
    void operator() (std::list< typename GMap<KEY, VALUE>::Node > list);
};

template<typename KEY, typename VALUE>
class GMap
{
public:
    GMap(){m_size = 0;}

    void insert(KEY key, VALUE value);
    void pop();
    void remove(KEY key);
    KEY find(VALUE value)const;
    size_t size() const;
    void print_map();

private:
    struct Node
    {
        KEY m_key;
        VALUE m_value;
    };
    std::list< Node > m_list;
    size_t m_size;

};

template<typename KEY, typename VALUE>
void GMap<KEY, VALUE>::insert(KEY key, VALUE value)
{
    //why am I required to typename here?
    typename std::list< Node >::iterator iter = m_list.begin();

    while(iter != m_list.end())
    {
        if (iter->m_key == key)
        {
            return;
        }
        std::advance(iter, 1);
    }

    Node* new_node = new Node;
    new_node->m_key = key;
    new_node->m_value = value;

    m_list.push_back(*new_node);
    ++m_size;
}

template<typename KEY, typename VALUE>
void GMap<KEY, VALUE>::pop()
{
    if(0 == m_size)
    {
        return;
    }

    m_list.pop_back();
    --m_size;
}

template<typename KEY, typename VALUE>
void GMap<KEY, VALUE>::remove(KEY key)
{
    typename std::list< Node >::iterator iter = m_list.begin();

    while(iter != m_list.end())
    {
        if (iter->m_key == key)
        {
            m_list.erase(iter);
            --m_size;
            return;
        }
        std::advance(iter, 1);
    }

}

template<typename KEY, typename VALUE>
size_t GMap<KEY, VALUE>::size() const
{
    return m_size;
}

template<typename KEY, typename VALUE>
KEY GMap<KEY, VALUE>::find(VALUE value) const
{
    //this line is the only thing that seems to be giving me compiler errors
    //can you explain what I am overlooking?
    typename std::list< Node >::iterator iter = m_list.begin();

    while(iter != m_list.end())
    {
        if (iter->m_value == value)
        {
            return iter->m_key;
        }
        std::advance(iter, 1);
    }
    return NULL;
}

//I know this I not what you request I have it just for testing my idea at least
//I am struggling to see how to use the MapPrinter class which I am treating as a functor
template<typename KEY, typename VALUE>
void GMap<KEY, VALUE>::print_map()
{
    typename std::list< Node >::iterator iter = m_list.begin();

    while(iter != m_list.end())
    {
        std::cout << iter->m_key << " " << iter->m_value << std::endl;
        std::advance(iter, 1);
    }
}

int main()
{
    GMap<int, std::string> map;

    //size test
    std::cout << "size = " << map.size() << std::endl;

    //insert test
    map.insert(2, "Hello");
    std::cout << "size = " << map.size() << std::endl;
    map.insert(2, "world");
    std::cout << "size = " << map.size() << std::endl;

    //pop test
    map.insert(3, "world");
    std::cout << "size = " << map.size() << std::endl;
    map.pop();
    std::cout << "size = " << map.size() << std::endl;

    //remove test
    map.insert(3, "world");
    map.remove(2);
    std::cout << "size = " << map.size() << std::endl;

    //find test
    map.insert(2, "Hello");
    map.insert(1, "Hello");
    map.insert(4, "Hello");
    map.print_map();
    //std::cout << "found at = " << map.find("world") << std::endl;

    return 0;
}