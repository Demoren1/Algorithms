#include <iostream>
#include <vector>

int main()
{
    int N = 0;
    std::cin >> N;

    int result = -99999;
    int l_index = 0;
    int r_index = 0;

    int tmp_value = 0;
    int tmp_sum = 0;

    for (int i = 0; i != N; ++i)
    {
        std::cin >> tmp_value;
        tmp_sum += tmp_value;

        if (tmp_sum > result)
        {
            result = tmp_sum;
            r_index = i;
        }

        if (tmp_sum < 0)
        {
            tmp_sum = 0;
            l_index = r_index + 1;
        }
    }
    ++l_index;
    ++r_index;
    // std::cout << l_index;
    // std::cout << ' ';
    // std::cout << r_index;
    // std::cout << ' ';
    // std::cout << result;

    printf("%d %d %d", l_index, r_index, result);

    return 0;
}























