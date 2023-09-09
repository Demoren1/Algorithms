#include <iostream>
#include <vector>


template<typename T>
class PrefixSums
{
  private:
    std::vector<T> prefix_sums;
  public:
    PrefixSums(const std::vector<T>& origin)
    {
        T current_sum = origin[0];
        size_t size = origin.size();

        prefix_sum.resize(size);
        prefix_sums[0] = current_sum;

        for (size_t i = 1; i < size; ++i)
        {
            current_sum += origin[i];
            prefix_sum[i] += current_sum;
        }
    }

    T get_sum(size_t l_index, size_t r_index)
    {
        T result = prefix_sums[r_index];

        if (l_index > 0)
        {
            result -= prefix_sums[l_index - 1];
        }

        return result;
    }
    T operator()(int index)
    {
        return prefix_sums[index];
    }
};