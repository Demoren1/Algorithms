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
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long n = 0;
    long long q = 0;
    std::cin >> n;
    std::vector<long long> smeshariks;

    long long tmp_value;
    for (long long i = 0; i != n; ++i)
    {
        std::cin >> tmp_value;
        smeshariks.push_back(tmp_value);
    }

    Fenvic<long long> fenvic_tree(smeshariks);

    std::cin >> q;

    char managing_char = 'a';
    long long first_tmp = 0;
    long long second_tmp = 0;
    for (long long i = 0; i != q; ++i)
    {
        std::cin >> managing_char >> first_tmp >> second_tmp;

        if (managing_char == 's') 
        {
            std::cout << fenvic_tree.sum(first_tmp - 1, second_tmp - 1) << ' ';
        }
        else
        {   
            second_tmp = second_tmp - fenvic_tree.sum(first_tmp - 1, first_tmp - 1);
            fenvic_tree.update(first_tmp - 1, second_tmp); 
        }
    }
    printf("\n");

    return 0;
}
