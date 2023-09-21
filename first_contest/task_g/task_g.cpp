#include <iostream>
#include <vector>

template <typename T>
class SegmentTree {
 private:
  std::vector<T> segment_tree_ = {};
  T (*seg_foo_)(T&, T&);
  int poison_ = 0xBADF00D;
  size_t origin_size_;
  size_t new_origin_size_;
  int n_log_ = 0;

 public:
  SegmentTree(std::vector<T>& origin, T (*seg_foo)(T&, T&)) : seg_foo_(seg_foo), origin_size_(origin.size()) {
    size_t n = 0;
    size_t size = origin.size();

    if (size % 2 == 0) {
      --n;
    }

    while (size > 0) {
      n++;
      size = size >> 1;
    }

    origin.resize(2 << n);
    new_origin_size_ = origin.size();
    segment_tree_.resize(2 << (n + 1));

    int n2 = 2 << n;
    int max_val = 2 << (n + 1);
    for (int i = n2; i != max_val; ++i) {
      segment_tree_[i] = origin[i - n2];
    }

    for (int i = n2 - 1; i > 0; --i) {
      segment_tree_[i] = seg_foo_(segment_tree_[i << 1], segment_tree_[(i << 1) + 1]);
    }
  }

 public:
  T GetElementOnSegment(size_t l_index, size_t r_index) {
    return GetElementOnSegment(l_index, r_index, 0, new_origin_size_ - 1, 1);
  }

 private:
  T GetElementOnSegment(size_t l_index, size_t r_index, size_t l, size_t r, size_t start = 1) {
    T result = segment_tree_[start];

    if (r_index < l || l_index > r) {
      return {poison_, 0};
    }

    if (l_index <= l && r_index >= r) {
      return result;
    }

    T x1 = GetElementOnSegment(l_index, r_index, l, (l + r) / 2, start * 2);
    T x2 = GetElementOnSegment(l_index, r_index, l / 2 + (r + 1) / 2, r, (start * 2) + 1);
    return seg_foo_(x1, x2);
  }

 public:
  void Update(size_t index, const T& value) {
    if (index + 1 > origin_size_) {
      return;
    }

    size_t tree_index = index + new_origin_size_;
    segment_tree_[tree_index] = value;

    tree_index /= 2;
    for (; tree_index != 0; tree_index /= 2) {
      segment_tree_[tree_index] = seg_foo_(segment_tree_[tree_index * 2], segment_tree_[tree_index * 2 + 1]);
    }
  }
};

struct Node {
  int value;
  int equal_sons = 0;
};

Node Foo(Node& first, Node& second) {
  int poison = 0xBADF00D;
  if (first.value == poison && second.value == poison) {
    return {poison, 0};
  }
  if (first.value == poison) {
    return second;
  }
  if (second.value == poison) {
    return first;
  }
  if (first.value > second.value) {
    return first;
  }
  if (first.value == second.value) {
    return {first.value, first.equal_sons + second.equal_sons};
  }
  return second;
}

int main() {
  int n = 0;
  int tmp_num = 0;
  std::cin >> n;
  std::vector<Node> tmp_vector;
  for (int i = 0; i < n; ++i) {
    std::cin >> tmp_num;
    tmp_vector.push_back({tmp_num, 1});
  }

  SegmentTree<Node> segment_tree(tmp_vector, Foo);

  int k = 0;
  int first = 0;
  int second = 0;
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    std::cin >> first >> second;
    Node tmp_node = segment_tree.GetElementOnSegment(first - 1, second - 1);
    std::cout << tmp_node.value << ' ' << tmp_node.equal_sons << '\n';
  }

  return 0;
}
