#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <typeinfo>

bool Compare(int x, int y)
{
    return x < y;
}

int main()
{
    std::vector<int> vec{7, 4, 2, 1, 64, 53, 12, 3, 4, 123, 23};

    std::sort(vec.begin(), vec.end(), Compare);

    for (const auto& element: vec)
    {
        std::cout << element << '\n';
    }

    return 0;
}

