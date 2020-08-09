#include <stdlib.h>
#include <array>
#include <iostream>

class Array
{
public:
    Array(int size);
    ~Array();//added to ensure no memory leaks
    void setval(int indx, int val);
    int getval(int indx);
    void setall(int val);

private:
    struct element
    {
        int val;
        size_t count;
    };

    element m_all;
    element* m_array; //Changed to pointer due to an issue with needing a const for array size
};

Array::Array(int size)
{
    m_all = {0};
    m_array = new element[size]; //allows the array to be of varrying size
}

Array::~Array()
{
    delete[] m_array;
}

void Array::setall(int val)
{
    m_all.val = val;
    m_all.count += 1;
}

void Array::setval(int indx, int val)
{
    m_array[indx].val = val;
    m_array[indx].count = m_all.count + 1;
}

int Array::getval(int indx)
{
    if (m_array[indx].count > m_all.count)
    {
        return m_array[indx].val;
    }
    return m_all.val;
}

int main()
{
    Array arr(10);

    std::cout << "index 3 = " << arr.getval(3) << std::endl;
    
    arr.setval(3, 3);
    std::cout << "index 3 = " << arr.getval(3) << std::endl;

    arr.setall(0);
    std::cout << "index 3 = " << arr.getval(3) << std::endl;

    return 0;
}