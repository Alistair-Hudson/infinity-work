/*******************************************************************************
                                * TEMPLATE FOR BIT ARRAY
                                * version 06.07.2020.0
******************************************************************************/

/****FUNCTORS****/
class FlipFunctor
{
public:
    FlipFunctor(bool b): MASK(b){}
    void operator () (bool& arr_bool)const {arr_bool^=MASK;}
    
private:
    bool MASK;
};

class App2String
{
public:
    App2String(std::string* s):m_string(s){}
    void operator () (const bool& arr_bool) 
    {
        if(arr_bool)
        {
            m_string->push_back('1');
        }
        else
        {
            m_string->push_back('0');
        }
    }
private:
    std::string* m_string;
};

class Shift
{
public:
    Shift(int n): shift(n){}
    bool operator() (bool& arr_bool)const {return arr_bool;}
private:
    int shift;
};


/****METHODS****/
template<size_t Size>
BitArray<Size>::BitArray()
{
    m_barray = {0};
    m_size = Size;
}

template<size_t Size>
BitArray<Size>& BitArray<Size>::SetAll()
{
    m_barray.fill(1);
    return *this;
}

template<size_t Size>
BitArray<Size>& BitArray<Size>::Set(size_t pos, bool val)
{
    try
    {
        if (pos > m_size || pos < 0)
        {
            throw 1;
        }
    }
    catch(int e)
    {
        std::cout << "Position is out of range" << std::endl;
        return *this;
    }
    m_barray.at(pos) = val;
    
    return *this;
}

template<size_t Size>
bool BitArray<Size>::Get(size_t pos) const
{
    try
    {
        if (pos > m_size || pos < 0)
        {
            throw 1;
        }
    }
    catch(int e)
    {
        std::cout << "Position is out of range" << std::endl;
        return 0;
    }
    return m_barray.at(pos);
}

template<size_t Size>
BitArray<Size>& BitArray<Size>::FlipAll()
{
    std::for_each(m_barray.begin(), m_barray.end(), FlipFunctor(1));
    return *this;
}

template<size_t Size>
BitArray<Size>& BitArray<Size>::Flip(size_t pos)
{
    try
    {
        if (pos > m_size || pos < 0)
        {
            throw 1;
        }
    }
    catch(int e)
    {
        std::cout << "Position is out of range" << std::endl;
        return *this;
    }
    
    m_barray.at(pos) ^= 1;
    
    return *this;
}

template<size_t Size>
size_t BitArray<Size>::CountBitsOn() const
{
    int count = 0;
    return std::accumulate(m_barray.begin(), m_barray.end(), count);
}

template<size_t Size>
std::string BitArray<Size>::ToString() const
{
    std::string ret;
    std::for_each(m_barray.begin(), m_barray.end(), App2String(&ret));
    return ret;
}

template<size_t Size>
const bool& BitArray<Size>::operator[](size_t pos)const
{
    return m_barray.at(pos);
}

template<size_t Size>
bool& BitArray<Size>::operator[](size_t pos)
{
    return m_barray.at(pos);
}

template<size_t Size>
bool BitArray<Size>::operator== (const BitArray& o_) const
{
    return equal(m_barray.begin(), m_barray.end(), m_barray.begin());
}

template<size_t Size>
bool BitArray<Size>::operator!= (const BitArray& o_) const
{
    return !equal(m_barray.begin(), m_barray.end(), m_barray.begin());
}

template<size_t Size>
BitArray<Size>& BitArray<Size>::operator&= (const BitArray& o_)
{
    std::transform(m_barray.begin(), m_barray.end(), &o_[0], m_barray.begin(), std::bit_and<bool>());
    return *this;
}

template<size_t Size>
BitArray<Size>& BitArray<Size>::operator|= (const BitArray& o_)
{
    std::transform(m_barray.begin(), m_barray.end(), &o_[0], m_barray.begin(), std::bit_or<bool>());
    return *this;
}

template<size_t Size>
BitArray<Size>& BitArray<Size>::operator^= (const BitArray& o_)
{
    std::transform(m_barray.begin(), m_barray.end(), &o_[0], m_barray.begin(), std::bit_xor<bool>());
    return *this;
}

template<size_t Size>
BitArray<Size>& BitArray<Size>::operator<<= (size_t shift)
{
    if (shift >= m_size)
    {
        m_barray.fill(0);
        return *this;
    }

    std::transform(std::next(m_barray.begin(), shift), m_barray.end(), m_barray.begin(), Shift(shift));
    std::fill(std::next(m_barray.begin(), shift+1), m_barray.end(), 0);
    return *this;
}

template<size_t Size>
BitArray<Size>& BitArray<Size>::operator>>= (size_t shift)
{
    if (shift >= m_size)
    {
        m_barray.fill(0);
        return *this;
    }

    std::transform(m_barray.begin(), std::next(m_barray.begin(), shift+1), std::next(m_barray.begin(), shift), Shift(shift));
     std::fill(m_barray.begin(), std::next(m_barray.begin(), shift), 0);
    return *this;
}

