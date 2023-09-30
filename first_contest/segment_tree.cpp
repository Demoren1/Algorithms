#include <iostream>
#include <vector>

template <typename T>
void update_on_node(T& node_value, const T& value);

template <typename T>
struct Node
{
    T value;
    T promise = 0;
};

template <typename T>
struct carried_update_on_node
{
    T standart_value;
    carried_update_on_node(const T& standart_value) : standart_value(standart_value)
    {}

    void operator()(T& node_value, const T& value)
    {
        update_on_node(node_value, value);
    }
};

template<typename T>
class SegmentTree
{
  private:
    std::vector<Node<T>> segment_tree;
    T (*seg_foo)(T, T);
    int POISON = 0xBADF00D;
    size_t actual_origin_size;
    size_t size_origin;
    int n_log = 0;

  public:
    SegmentTree(std::vector<T>& origin, T (*seg_foo)(T, T)): seg_foo(seg_foo), actual_origin_size(origin.size())
    {
        size_t n = -1;
        size_t size = origin.size();

        if (size % 2 == 0)
            --n;
        
        while(size > 0)
        {
            n++;
            size = size >> 1;
        }

        origin.resize(2 << n);
        size_origin = origin.size();
        segment_tree.resize(2 << (n + 1));
        segment_tree[0].value = 0;

        int n2 = 2 << n;
        int max_val = 2 << (n + 1);
        for (int i = n2; i != max_val; ++i)
        {
            segment_tree[i].value = origin[i - n2];
        }

        for (int i = n2 - 1; i > 0; --i)
        {   
            segment_tree[i].value = seg_foo(segment_tree[i << 1].value, segment_tree[(i << 1) + 1].value);
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
            sprintf(tmp_string, "node_%d [rank = %d, label = \"v = %d | p = %d\"];\n", i, i, segment_tree[i].value, 
              segment_tree[i].promise);
            fputs(tmp_string, log_file);

            sprintf(tmp_string, "node_%d [rank = %d, label = \"v = %d | p = %d\"];\n", 2*i, 2*i, segment_tree[2*i].value,
              segment_tree[2*i].promise);
            fputs(tmp_string, log_file);

            sprintf(tmp_string, "node_%d [rank = %d, label = \"v = %d | p = %d\"];\n", 2*i+1, 2*i, segment_tree[2*i + 1].value,
              segment_tree[2*i + 1].promise);
            fputs(tmp_string, log_file);

            sprintf(tmp_string, "node_%d-> node_%d;\n", i, 2*i);
            fputs(tmp_string, log_file);
            sprintf(tmp_string, "node_%d-> node_%d;\n", i, 2*i+1);
            fputs(tmp_string, log_file);
        }
        delete[] tmp_string;

        fputs("}\n", log_file);

        char* command = new char[256];

        fclose(log_file);
        sprintf(command, "dot -Tjpeg %s > jpeg_logs/dump_%d.jpeg", log_file_name, n_log++);
        system(command);

        delete[] command;
    }
  public:
    T get_element_on_segment(size_t l_index, size_t r_index, carried_update_on_node<T>& update_on_node)
    {   
        return get_element_on_segment(l_index, r_index, 0, size_origin - 1, 1, update_on_node);
    }
    void update_on_segment(size_t l_index, size_t r_index, carried_update_on_node<T>& update_on_node)
    {
        update_on_segment(l_index, r_index, update_on_node, 1, 0, size_origin - 1);
    }
    
  private:
    T get_element_on_segment(size_t l_index, size_t r_index, size_t L, size_t R, size_t start, carried_update_on_node<T>& update_on_node)
    {   
        // printf("start = %zd\n", start);
        // printf("l = %zd, r = %zd \n", l_index, r_index);
        // printf("L = %zd, R = %zd \n", L, R);

        if (r_index < L || l_index > R)
        {
            // std::cout << "POISON \n";
            return POISON;
        }
         
        if (l_index <= L && r_index >= R)
        {  
            push_until_end(start, update_on_node);
            segment_tree[start].promise = 0;

            Node<T> tmp_node = segment_tree[start];

            update_on_node(tmp_node.value, tmp_node.promise);
            return tmp_node.value;
        }

        push(start, update_on_node);
        
        T x1 = get_element_on_segment(l_index, r_index, L, (L + R) / 2, start * 2, update_on_node);
        T x2 = get_element_on_segment(l_index, r_index, L / 2 + (R + 1) / 2, R, (start * 2) + 1, update_on_node);
        
        // printf("x1 = %zd, x2 = %zd\n", x1, x2);

        T left_son_value = segment_tree[2 * start].value;
        update_on_node(left_son_value, segment_tree[2 * start].promise);

        T right_son_value = segment_tree[2 * start + 1].value;
        update_on_node(right_son_value, segment_tree[2 * start + 1].promise);

        segment_tree[start].value = seg_foo(left_son_value, right_son_value);

        return seg_foo(x1, x2);
    }
  public:
    void update(size_t index, const T& value)
    {   
        if (index + 1 > actual_origin_size)
            return;
            
        size_t tree_index = index + size_origin;
        segment_tree[tree_index].value = value;
        
        tree_index /= 2;
        for (; tree_index != 0; tree_index /= 2)
        {
            segment_tree[tree_index].value = seg_foo(segment_tree[tree_index * 2].value, segment_tree[tree_index * 2 + 1].value);
        }
    }
  private:
    void update_on_segment(size_t l_index, size_t r_index, carried_update_on_node<T>& update_on_node, size_t node_index, 
      size_t L_boundry, size_t R_boundry)
    {

        if (r_index < L_boundry || l_index > R_boundry)
        {
            return;
        }
         
        if (l_index <= L_boundry && r_index >= R_boundry)
        {
            update_on_node(segment_tree[node_index].promise, update_on_node.standart_value);
            if (2 * node_index + 1 >= 2 * size_origin)
            {
                update_on_node(segment_tree[node_index].value, segment_tree[node_index].promise);
                segment_tree[node_index].promise = 0;
            }
            return;
        }

        push(node_index, update_on_node);

        update_on_segment(l_index, r_index, update_on_node, 2 * node_index, L_boundry, (L_boundry + R_boundry) / 2);
        update_on_segment(l_index, r_index, update_on_node, 2 * node_index + 1, L_boundry / 2 + (R_boundry + 1) / 2, R_boundry);
        
        T left_son_value = segment_tree[2 * node_index].value;
        update_on_node(left_son_value, segment_tree[2 * node_index].promise);
        
        T right_son_value = segment_tree[2 * node_index + 1].value;
        update_on_node(right_son_value, segment_tree[2 * node_index + 1].promise);

        segment_tree[node_index].value = seg_foo(left_son_value, right_son_value);

        return;
    }
    void push(int node_index, carried_update_on_node<T>& update_on_node)
    {   
        update_on_node(segment_tree[2 * node_index].promise, segment_tree[node_index].promise);
        update_on_node(segment_tree[2 * node_index + 1].promise, segment_tree[node_index].promise);

        segment_tree[node_index].promise = 0;
    }

    void push_until_end(size_t node_index, carried_update_on_node<T>& update_on_node)
    {
        if (2 * node_index + 1 < 2 * size_origin)
        {
            update_on_node(segment_tree[2 * node_index].promise, segment_tree[node_index].promise);
            update_on_node(segment_tree[2 * node_index + 1].promise, segment_tree[node_index].promise);

            segment_tree[node_index].promise = 0;

            push_until_end(2 * node_index, update_on_node);
            push_until_end(2 * node_index + 1, update_on_node);

            segment_tree[node_index].value = seg_foo(segment_tree[2 * node_index].value, segment_tree[2 * node_index + 1].value);
        }

        update_on_node(segment_tree[node_index].value, segment_tree[node_index].promise);
        segment_tree[node_index].promise = 0;
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
    return first + second;
}

template <typename T>
void update_on_node(T& node_value, const T& value)
{   
    node_value += value;
}


int main()
{   
    std::vector<int> tmp_vector = {0, 1, 2, 3, 4};
    SegmentTree<int> segment_tree(tmp_vector, foo);
    carried_update_on_node<int> our_update(1);

    segment_tree.show_tree();
    // segment_tree.update(0, 5);
    // segment_tree.update(6, 3);

    int sum = segment_tree.get_element_on_segment(0, 3, our_update);
    // printf("sum = %d\n", sum);
    // segment_tree.show_tree();
    

    segment_tree.update_on_segment(0, 3, our_update);
    segment_tree.show_tree();
    sum = segment_tree.get_element_on_segment(0, 3, our_update);
    printf("sum = %d\n", sum);

    segment_tree.show_tree();


    // for (int i = 0; i < tmp_vector.size(); ++i)
    // {
    //     for (int j = i + 1; j < tmp_vector.size(); ++j)
    //     {
    //         std::cout << segment_tree.get_element_on_segment(i, j, 0, tmp_vector.size() - 1) << " || i = " << i << " || j = " << j << '\n'; 
    //     }
    // }

    return 0;
}

