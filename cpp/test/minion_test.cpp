#include "minion.hpp"

int main()
{
    ilrd::Minion test_minion(8081, 52743, 8081);

    test_minion.Run();

    return 0;
}