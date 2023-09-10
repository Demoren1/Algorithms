#include <iostream>
#include <vector>

int gcd(int first, int second);

template<typename T>
class SegmentTree
{
  private:
    std::vector<T> segment_tree = {0};
    T (*seg_foo)(T, T);
    int POISON = 0xBADF00D;
    size_t size_origin;

  public:
    SegmentTree(std::vector<T>& origin, T (*seg_foo)(T, T)): seg_foo(seg_foo)
    {
        size_t n = 0;
        size_t size = origin.size();

        if (size % 2 == 0)
         --n;
        
        while(size > 0)
        {
            n++;
            size = size >> 1;
        }
        // --n;


        origin.resize(2 << n);
        size_origin = origin.size();
        segment_tree.resize(2 << (n + 1));
        segment_tree[0] = 0;

        int max_val = 2 << (n + 1);
        int n2 = 2 << n;

        for (int i = n2; i != max_val; ++i)
        {
            segment_tree[i] = origin[i - n2];
        }

        for (int i = n2 - 1; i > 0; --i)
        {   
            // std::cout << i;
            segment_tree[i] = seg_foo(segment_tree[i << 1], segment_tree[(i << 1) + 1]);
        }
    }

    void show_tree()
    {
        size_t size = segment_tree.size();
        for (size_t i = 0; i != size; ++i)
            std::cout << segment_tree[i] << ' ';
        std::cout << '\n';
    }

    inline T get_element_on_segment(size_t l_index, size_t r_index, size_t L, size_t R, size_t start = 1) // L = 0, R = Размер исходного вектора
    {
        // std::cout << L << ' ' << R << '\n';
        T result = segment_tree[start];

        if (r_index < L || l_index > R)
            return POISON;
         
        else if (l_index <= L && r_index >= R)
        {
            return result;
        }

        else
        {
            T x1 = get_element_on_segment(l_index, r_index, L, (L + R) / 2, start * 2);
            T x2 = get_element_on_segment(l_index, r_index, L / 2 + (R + 1) / 2, R, (start * 2) + 1);

            return seg_foo(x1, x2);
        }
    }
};


int foo(int first, int second)
{   
    int POISON = 0xBADF00D;
    if (first == POISON && second == POISON)
        return POISON;
    else if (first == POISON)
        return second;
    else if (second == POISON)
        return first;

    // return std::min(first, second);
    // return first + second;
    return gcd(first, second);
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    int q = 0;
    std::cin >> n;
    std::vector<int> smeshariks;

    int tmp_value;
    for (int i = 0; i != n; ++i)
    {
        std::cin >> tmp_value;
        smeshariks.push_back(tmp_value);
    }

    SegmentTree<int> segment_tree(smeshariks, foo);

    int l_index = 0;
    int r_index = 0;

    std::cin >> q;
    for (int i = 0; i != q; ++i)
    {
        std::cin >> l_index >> r_index;
        printf("%d \n", segment_tree.get_element_on_segment(l_index - 1, r_index - 1, 0, smeshariks.size() - 1));
    }

    return 0;
}


int gcd(int first, int second) 
{
    while (second != 0) 
    {
        int temp = second;
        second = first % second;
        first = temp;
    }
    return first;
}