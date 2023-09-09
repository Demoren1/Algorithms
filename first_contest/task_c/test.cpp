#include <iostream>
#include <vector>
#include <cmath>

template<typename T>
class SegmentTree
{
private:
    std::vector<T> segment_tree;
    std::function<T(T, T)> seg_foo;

public:
    SegmentTree(std::vector<T>& origin, T (*seg_foo)(T, T)): seg_foo(seg_foo)
    {
        size_t n = std::log2(origin.size()) + 1;

        origin.resize(1 << n);
        segment_tree.resize(1 << (n + 1));

        for (size_t i = (1 << n); i < (1 << (n + 1)); ++i)
        {
            segment_tree[i] = origin[i - (1 << n)];
        }

        for (size_t i = (1 << n) - 1; i > 0; --i)
        {
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

    inline T get_element_on_segment(size_t l_index, size_t r_index, size_t L, size_t R, size_t start = 1)
    {
        T result = segment_tree[start];
        size_t mid = (L + R) >> 1; // Быстрое вычисление среднего

        if (r_index < L || l_index > R)
            return 0;

        if (l_index <= L && r_index >= R)
            return result;

        T x1 = get_element_on_segment(l_index, r_index, L, mid, start << 1);
        T x2 = get_element_on_segment(l_index, r_index, mid + 1, R, (start << 1) + 1);

        return seg_foo(x1, x2);
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

    return std::min(first, second);
    // return first + second;
}

int main()
{
    int n = 0;
    int q = 0;
    std::cin >> n >> q;
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

    // segment_tree.show_tree();
    for (int i = 0; i != q; ++i)
    {
        std::cin >> l_index >> r_index;
        std::cout << segment_tree.get_element_on_segment(l_index - 1, r_index - 1, 0, smeshariks.size() - 1) << '\n';
    }

    return 0;
}