#include <iostream>
#include <vector>

long long get_sum(long long start, long long finish, const std::vector<long long>& prefix_sums);

int main()
{
    std::ios_base::sync_with_stdio(false);

    size_t N;
    std::cin >> N;
    std::vector<long long> prefix_sums(N, 0);
    
    long long score;
    std::cin >> score;

    long long prefix_sum = score;
    prefix_sums[0] += prefix_sum;

    for (size_t i = 1; i < N; ++i)
    {
        std::cin >> score;

        prefix_sum += score;
        prefix_sums[i] += prefix_sum;
    }

    long long K = 0;
    std::cin >> K;

    for (long long i = 0; i != K; ++i)
    {
        long long start, finish;
        std::cin >> start >> finish;
        std::cout << get_sum(start - 1, finish - 1, prefix_sums) << '\n';
    }

    return 0;
}

inline long long get_sum(long long start, long long finish, const std::vector<long long>& prefix_sums)
{
    long long sum = prefix_sums[finish];
    if (start > 0)
        sum -= prefix_sums[start - 1];
    return sum;
}