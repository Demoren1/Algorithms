#include <iostream>
#include <vector>


template<typename T>
class SegmentTree
{
  private:
    std::vector<T> segment_tree = {0};
    T (*seg_foo)(T, T);
    int POISON = 0xBADF00D;
    size_t actual_origin_size;
    size_t size_origin;
    int n_log = 0;

  public:
    SegmentTree(std::vector<T>& origin, T (*seg_foo)(T, T)): seg_foo(seg_foo)
    {
        size_t n = 0;
        size_t size = origin.size();

        if (size % 2 == 0)
        {
            --n;
        }
        
        while(size > 0)
        {
            n++;
            size = size >> 1;
        }
        
        actual_origin_size = origin.size();
        origin.resize(2 << n);
        size_origin = origin.size();
        segment_tree.resize(2 << (n + 1));
        segment_tree[0] = POISON;

        int n2 = 2 << n;
        int max_val = 2 << (n + 1);
        for (int i = n2; i != max_val; ++i)
        {
            segment_tree[i] = origin[i - n2];
        }

        for (int i = n2 - 1; i > 0; --i)
        {   
            segment_tree[i] = seg_foo(segment_tree[i << 1], segment_tree[(i << 1) + 1]);
        }
    }

    void show_tree()
    {   
        const char* log_file_name = "logs.txt";
        FILE* log_file = fopen(log_file_name, "w");

        size_t size = segment_tree.size();

        fputs("digraph{\n", log_file);
        fputs("rankdir = HR;\n", log_file);
        fputs("bgcolor = grey;\n", log_file);

        char* tmp_string = new char[256];
        for (int i = 1; i != size / 2; ++i)
        {   
            sprintf(tmp_string, "node_%d [rank = %d, label = %d];\n", i, i, segment_tree[i]);
            fputs(tmp_string, log_file);

            sprintf(tmp_string, "node_%d [rank = %d, label = %d];\n", 2*i, 2*i, segment_tree[2*i]);
            fputs(tmp_string, log_file);

            sprintf(tmp_string, "node_%d [rank = %d, label = %d];\n", 2*i+1, 2*i, segment_tree[2*i + 1]);
            fputs(tmp_string, log_file);

            sprintf(tmp_string, "node_%d-> node_%d;\n", i, 2*i);
            fputs(tmp_string, log_file);
            sprintf(tmp_string, "node_%d-> node_%d;\n", i, 2*i+1);
            fputs(tmp_string, log_file);
        }
        delete []tmp_string;

        fputs("}\n", log_file);

        char* command = new char[256];

        fclose(log_file);
        sprintf(command, "dot -Tjpeg %s > jpeg_logs/dump_%d.jpeg", log_file_name, n_log++);
        system(command);

        delete []command;
    }

    T get_element_on_segment(size_t l_index, size_t r_index, size_t L, size_t R, size_t start = 1)
    {
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
            T x2 = get_element_on_segment(l_index, r_index, (L + R + 1) / 2, R, start * 2 + 1);

            return seg_foo(x1, x2);
        }

        return result;
    }

    void update(size_t index, const T& value)
    {   
        if (index + 1 > actual_origin_size)
            return;
            
        size_t tree_index = index + size_origin;
        segment_tree[tree_index] = value;
        
        tree_index /= 2;
        for (; tree_index != 0; tree_index /= 2)
        {
            segment_tree[tree_index] = seg_foo(segment_tree[tree_index * 2], segment_tree[tree_index * 2 + 1]);
        }
    }

};


long long foo(long long first, long long second)
{   
    int POISON = 0xBADF00D;
    if (first == POISON && second == POISON)
        return POISON;
    else if (first == POISON)
        return second;
    else if (second == POISON)
        return first;

    // return std::min(first, second);
    return first + second;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    int q = 0;
    std::cin >> n;
    std::vector<long long> smeshariks;

    long long tmp_value;
    for (int i = 0; i != n; ++i)
    {
        std::cin >> tmp_value;
        smeshariks.push_back(tmp_value);
    }

    SegmentTree<long long> segment_tree(smeshariks, foo);

    std::cin >> q;

    char managing_char = 'a';
    int first_tmp = 0;
    int second_tmp = 0;
    for (int i = 0; i != q; ++i)
    {
        std::cin >> managing_char >> first_tmp >> second_tmp;

        if (managing_char == 's') 
            std::cout << segment_tree.get_element_on_segment(first_tmp - 1, second_tmp - 1, 0, smeshariks.size() - 1) << ' ';
        else
        {   
            segment_tree.update(first_tmp - 1, second_tmp); 
        }
    }
    std::cout << '\n';

    return 0;
}
