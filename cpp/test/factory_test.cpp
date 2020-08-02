#include <iostream>

#include <string>
#include <boost/function.hpp>

#include "factory.hpp"

using namespace ilrd;

class Test
{
public:
    Test(std::string name = "test");
    virtual ~Test(){};
    std::string m_name;
};

Test::Test(std::string name)
{
    m_name = name;
    std::cout << m_name << std::endl;
}

class Covid : public Test
{
public:
    Covid(std::string name = "covid")
    {
        m_name = name;
        std::cout << "covid test created" << std::endl;
    }

    ~Covid(){};
};

class Flu : public Test
{
public:
    Flu(std::string name = "flu")
    {
        m_name = name;
        std::cout << "flu test created" << std::endl;
    }

    ~Flu(){};
};

Test *NewTest(std::string name)
{
    Test *ret = new Test(name);

    return (ret);
}

Test *NewCovid(std::string name)
{
    Test *ret = new Covid(name);

    return (ret);
}

Test *NewFlu(std::string name)
{
    Test *ret = new Flu(name);

    return (ret);
}



int main()
{
    Factory<std::string, Test, std::string> teva;

    boost::function<Test *(std::string)> test = NewTest;
    boost::function<Test *(std::string)> covid = NewCovid;
    boost::function<Test *(std::string)> flu = NewFlu;
    
    std::string s_test("test");

    test("wow");

    teva.Add(s_test, NewTest);
    teva.Add("covid", NewCovid);
    teva.Add("flu", NewFlu);

    teva.Create("covid", "covid");
    teva.Create("flu", "flu");
    teva.Create("test", "test");

    return (0);
}