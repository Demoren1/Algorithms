#include <iostream>
#include <vector>

int main()
{
    int N = 0;
    std::cin >> N;

    int result = -9999;
    int l_index = 0;
    int r_index = 0;
    int minus_pos = -1;

    int tmp_value = 0;
    int tmp_sum = 0;

    for (int i = 0; i != N; ++i)
    {

        std::cin >> tmp_value;
        tmp_sum += tmp_value;

        if (tmp_sum > result)
        {
            result = tmp_sum;
            l_index = minus_pos + 1;
            r_index = i;
        }

        // std::cout << tmp_sum << ' ' << i << ' ' << l_index << '\n';

        if (tmp_sum < 0)
        {
            minus_pos = i;
            tmp_sum = 0;
        }
    }

    
    std::cout << l_index + 1 << ' ' << r_index + 1 << ' ' << result << '\n';
    return 0;
}









































