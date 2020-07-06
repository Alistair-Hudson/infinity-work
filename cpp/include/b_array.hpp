#ifndef __BIT_ARRAY_HPP__
#define __BIT_ARRAY_HPP__

/*******************************************************************************
                                * API FOR BIT ARRAY
                                * version 05.07.2020.0
******************************************************************************/

#include <iostream>
#include <array>
#include <algorithm>
#include <numeric>
#include <string>
#include <functional>

class BitProxy;

template<size_t Size>
class BitArray
{
public:
    BitArray();
    BitArray& SetAll();
    BitArray& Set(size_t pos, bool val);
    bool Get(size_t pos) const;
    BitArray& FlipAll();
    BitArray& Flip(size_t pos);
    size_t CountBitsOn() const;
    std::string ToString() const;

    const bool& operator[](size_t pos)const;
    bool& operator[](size_t pos);
    bool operator == (const BitArray& o_) const;
    bool operator != (const BitArray& o_) const;
    BitArray& operator &= (const BitArray& o_);
    BitArray& operator |= (const BitArray& o_);
    BitArray& operator ^= (const BitArray& o_);
    BitArray& operator <<= (size_t shift);
    BitArray& operator >>= (size_t shift);

private:
    std::array<bool, Size> m_barray;
    size_t m_size;

};

class BitProxy
{
public:
    BitProxy(bool& byte, char index);
    BitProxy& operator= (bool val);
    operator bool() const;
    bool operator!() const;
private:
    bool& m_byte;
    char m_index;
};

#include "b_array.tpp"

#endif /* __BIT_ARRAY_HPP__ */
