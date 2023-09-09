#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
class SegmentTree
{
private:
    std::vector<T> segment_tree;
    T (*seg_foo)(T, T);
    size_t size_origin;

public:
    SegmentTree(const std::vector<T>& origin, T (*seg_foo)(T, T))
        : seg_foo(seg_foo), size_origin(origin.size())
    {
        int n = 1;
        while (n < size_origin) {
            n <<= 1;
        }
        segment_tree.resize(2 * n, 0);
        buildSegmentTree(origin, 0, 0, size_origin - 1);
    }

    void buildSegmentTree(const std::vector<T>& origin, int pos, int left, int right)
    {
        if (left == right) {
            segment_tree[pos] = origin[left];
            return;
        }

        int mid = left + (right - left) / 2;
        buildSegmentTree(origin, 2 * pos + 1, left, mid);
        buildSegmentTree(origin, 2 * pos + 2, mid + 1, right);
        segment_tree[pos] = seg_foo(segment_tree[2 * pos + 1], segment_tree[2 * pos + 2]);
    }

    T query(int qlow, int qhigh, int pos, int left, int right)
    {
        if (qlow <= left && qhigh >= right)
            return segment_tree[pos];
        if (qlow > right || qhigh < left)
            return 0;

        int mid = left + (right - left) / 2;
        T leftResult = query(qlow, qhigh, 2 * pos + 1, left, mid);
        T rightResult = query(qlow, qhigh, 2 * pos + 2, mid + 1, right);
        return seg_foo(leftResult, rightResult);
    }

    T get_element_on_segment(int l_index, int r_index)
    {
        return query(l_index, r_index, 0, 0, size_origin - 1);
    }
};

int foo(int first, int second)
{
    return std::min(first, second);
}

int main()
{
    int n, q;
    std::cin >> n >> q;
    std::vector<int> smeshariks(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> smeshariks[i];
    }

    SegmentTree<int> segment_tree(smeshariks, foo);

    for (int i = 0; i < q; ++i)
    {
        int l_index, r_index;
        std::cin >> l_index >> r_index;
        std::cout << segment_tree.get_element_on_segment(l_index - 1, r_index - 1) << '\n';
    }

    return 0;
}
