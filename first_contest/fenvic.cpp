#include <iostream>
#include <vector>

template<typename T>
class Fenvic
{
  private:
    std::vector<T> F;
    size_t original_size;

  public:
    Fenvic(const std::vector<T>& original) : F(original.size(), 0), original_size(original.size())
    {
        for (size_t i = 0; i != original_size; ++i)
        {
            update(i, original[i]);
        }
    }

    void update(size_t n_element, const T& delta)
    {
        for (size_t i = n_element; i < original_size; i = i | (i + 1))
        {
            F[i] += delta;
        }
    }

    const T sum(int r_index)
    {
        T sum = 0;
        for (int i = r_index; i >= 0; i = (i & (i + 1)) - 1)
        {
            sum += F[i];
        }

        return sum;
    }

    const T sum(int l_index, int r_index)
    {
        return sum(r_index) - sum(l_index - 1);
    }

};


int main()
{
    Fenvic<int> test({1, 2, 3, 4});

    std::cout << test.sum(0, 0);
    return 0;
}


