#include <iostream>
#include <vector>


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
        --n;

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
    }

    T get_element_on_segment(size_t l_index, size_t r_index, size_t L, size_t R, size_t start = 1)
    {
        // std::cout << L << ' ' << R << '\n';
        T result = segment_tree[start];

        if (r_index < L || l_index > R)
            return POISON;
         
        if (l_index <= L && r_index >= R)
        {
            return result;
        }

        else
        {
            T x1 = get_element_on_segment(l_index, r_index, L, (L + R) / 2, start * 2);
            T x2 = get_element_on_segment(l_index, r_index, L / 2 + (R + 1) / 2, R, (start * 2) + 1);
            // std::cout << x1 << ' ' << x2 << '\n';
            return seg_foo(x1, x2);
        }

        return result;
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
    std::vector<int> tmp_vector = {1, 2, 2, 3, 1, 1, 4, 2};
    SegmentTree<int> segment_tree(tmp_vector, foo);

    // segment_tree.show_tree();

    std::cout << segment_tree.get_element_on_segment(5, 7, 0, tmp_vector.size() - 1) << '\n'; 
    return 0;
}

