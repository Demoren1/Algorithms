#include <iostream>
#include <vector>
#include <cmath>

template <typename T>
void UpdateOnNodeTrue(T& node_value, const T& value);

template <typename T>
struct Node {
  T value;
  T promise = 0;
  bool is_leaf = false;
};

template <typename T>
struct CarriedUpdateOnNode {
  T standart_value;

  explicit CarriedUpdateOnNode(const T& standart_value) : standart_value(standart_value) {
  }

  void operator()(T& node_value, const T& value) {
    UpdateOnNodeTrue(node_value, value);
  }
};

template <typename T>
class SegmentTree {
 private:
  std::vector<Node<T>> segment_tree_;
  T (*seg_foo_)(T&, T&);
  int poison_ = 0xBADF00D;
  size_t actual_origin_size_;
  size_t size_origin_;
  int n_log_ = 0;

 public:
  SegmentTree(std::vector<T>& origin, T (*seg_foo)(T&, T&)) : seg_foo_(seg_foo), actual_origin_size_(origin.size()) {
    size_t n = 0;  // dont touch
    size_t size = origin.size();

    n = static_cast<int>(log2(size)) + 1;
    if (size % 2 == 0) {
      --n;
    }

    origin.resize(2 << n);
    size_origin_ = origin.size();
    segment_tree_.resize(2 << (n + 1));
    segment_tree_[0].value = 0;

    int n2 = 2 << n;
    int max_val = 2 << (n + 1);
    for (int i = n2; i != max_val; ++i) {
      segment_tree_[i].value = origin[i - n2];
      segment_tree_[i].is_leaf = true;
    }

    for (int i = n2 - 1; i > 0; --i) {
      segment_tree_[i].value = seg_foo_(segment_tree_[i << 1].value, segment_tree_[(i << 1) + 1].value);
    }
  }

  void ShowTree() {
    const char* log_file_name = "logs.txt";
    FILE* log_file = fopen(log_file_name, "w");

    size_t size = segment_tree_.size();

    fputs("digraph{\n", log_file);
    fputs("rankdir = HR;\n", log_file);
    fputs("bgcolor = grey;\n", log_file);

    char* tmp_string = new char[256];
    for (int i = 1; i != size / 2; ++i) {
      sprintf(tmp_string, "node_%d [rank = %d, label = \"v = %ld | p = %ld\"];\n", i, i, segment_tree_[i].value,
              segment_tree_[i].promise);
      fputs(tmp_string, log_file);
      sprintf(tmp_string, "node_%d [rank = %d, label = \"v = %ld | p = %ld\"];\n", 2 * i, 2 * i,
              segment_tree_[2 * i].value, segment_tree_[2 * i].promise);
      fputs(tmp_string, log_file);
      sprintf(tmp_string, "node_%d [rank = %d, label = \"v = %ld | p = %ld\"];\n", 2 * i + 1, 2 * i,
              segment_tree_[2 * i + 1].value, segment_tree_[2 * i + 1].promise);

      fputs(tmp_string, log_file);
      sprintf(tmp_string, "node_%d-> node_%d;\n", i, 2 * i);
      fputs(tmp_string, log_file);
      sprintf(tmp_string, "node_%d-> node_%d;\n", i, 2 * i + 1);
      fputs(tmp_string, log_file);
    }
    delete[] tmp_string;
    fputs("}\n", log_file);

    char* command = new char[256];
    fclose(log_file);
    sprintf(command, "dot -Tjpeg %s > jpeg_logs/dump_%d.jpeg", log_file_name, n_log_++);
    system(command);

    delete[] command;
  }

 public:
  T GetElementOnSegment(size_t l_index, size_t r_index, CarriedUpdateOnNode<T>& update_on_node) {
    // PushUntilEnd(start, update_on_node);
    return GetElementOnSegment(l_index, r_index, 0, size_origin_ - 1, 1, update_on_node);
  }
  void UpdateOnSegment(size_t l_index, size_t r_index, CarriedUpdateOnNode<T>& update_on_node) {
    UpdateOnSegment(l_index, r_index, update_on_node, 1, 0, size_origin_ - 1);
  }

 private:
  T GetElementOnSegment(size_t l_index, size_t r_index, size_t l_boundry, size_t r_boundry, size_t start,
                        CarriedUpdateOnNode<T>& update_on_node) {
    if (r_index < l_boundry || l_index > r_boundry) {
      return poison_;
    }

    if (l_index <= l_boundry && r_index >= r_boundry) {
      Push(start, update_on_node);
      return segment_tree_[start].value;
    }
    Push(start, update_on_node);

    T x1 = GetElementOnSegment(l_index, r_index, l_boundry, (l_boundry + r_boundry) / 2, start * 2, update_on_node);
    T x2 = GetElementOnSegment(l_index, r_index, l_boundry / 2 + (r_boundry + 1) / 2, r_boundry, (start * 2) + 1,
                               update_on_node);

    return seg_foo_(x1, x2);
  }

 public:
  void Update(size_t index, const T& value) {
    if (index + 1 > actual_origin_size_) {
      return;
    }
    size_t tree_index = index + size_origin_;
    segment_tree_[tree_index].value = value;

    tree_index /= 2;
    for (; tree_index != 0; tree_index /= 2) {
      seg_foo_(segment_tree_[tree_index * 2].value, segment_tree_[tree_index * 2 + 1].value);
    }
  }

 private:
  void UpdateOnSegment(size_t l_index, size_t r_index, CarriedUpdateOnNode<T>& update_on_node, size_t node_index,
                       size_t l_boundry, size_t r_boundry) {
    if (r_index < l_boundry || l_index > r_boundry) {
      return;
    }

    if (l_index <= l_boundry && r_index >= r_boundry) {
      update_on_node(segment_tree_[node_index].promise, update_on_node.standart_value);
      return;
    }

    Push(node_index, update_on_node);

    UpdateOnSegment(l_index, r_index, update_on_node, 2 * node_index, l_boundry, (l_boundry + r_boundry) / 2);
    UpdateOnSegment(l_index, r_index, update_on_node, 2 * node_index + 1, l_boundry / 2 + (r_boundry + 1) / 2,
                    r_boundry);

    T left_son_value = segment_tree_[2 * node_index].value;
    update_on_node(left_son_value, segment_tree_[2 * node_index].promise);

    T right_son_value = segment_tree_[2 * node_index + 1].value;
    update_on_node(right_son_value, segment_tree_[2 * node_index + 1].promise);

    segment_tree_[node_index].value = seg_foo_(left_son_value, right_son_value);
  }
  void Push(size_t node_index, CarriedUpdateOnNode<T>& update_on_node) {
    if (!segment_tree_[node_index].is_leaf) {
      update_on_node(segment_tree_[2 * node_index].promise, segment_tree_[node_index].promise);
      update_on_node(segment_tree_[2 * node_index + 1].promise, segment_tree_[node_index].promise);
    }

    update_on_node(segment_tree_[node_index].value, segment_tree_[node_index].promise);
    segment_tree_[node_index].promise = 0;
  }

  void PushUntilEnd(size_t node_index, CarriedUpdateOnNode<T>& update_on_node) {
    Push(node_index, update_on_node);
    if (!segment_tree_[node_index].is_leaf) {
      PushUntilEnd(2 * node_index, update_on_node);
      PushUntilEnd(2 * node_index + 1, update_on_node);
    }
  }
};

template <typename T>
T Foo(T& first, T& second) {
  int poison = 0xBADF00D;
  if (first == poison && second == poison) {
    return poison;
  }
  if (first == poison) {
    return second;
  }
  if (second == poison) {
    return first;
  }

  // return std::min(first, second);
  // return first + second;
  return std::max(first, second);
}

template <typename T>
void UpdateOnNodeTrue(T& node_value, const T& value) {
  node_value += value;
}

void Solution();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  Solution();
  return 0;
}

void Solution() {
  CarriedUpdateOnNode<int> our_update(0);
  int n = 0;
  std::cin >> n;
  std::vector<int> beehive;

  int tmp_num = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> tmp_num;
    beehive.push_back(tmp_num);
  }

  SegmentTree<int> segment_beehive(beehive, Foo);

  int m = 0;
  char managin_char = 'a';
  std::cin >> m;

  int first = 0;
  int second = 0;
  int add = 0;
  // segment_beehive.ShowTree();

  for (int i = 0; i < m; ++i) {
    std::cin >> managin_char;

    switch (managin_char) {
      case 'm': {
        std::cin >> first >> second;
        our_update.standart_value = 0;
        int result = segment_beehive.GetElementOnSegment(first - 1, second - 1, our_update);
        std::cout << result << '\n';
        break;
      }
      case 'a': {
        std::cin >> first >> second >> add;

        our_update.standart_value = add;
        segment_beehive.UpdateOnSegment(first - 1, second - 1, our_update);
        break;
      }
    }
    // segment_beehive.ShowTree();
  }
}
