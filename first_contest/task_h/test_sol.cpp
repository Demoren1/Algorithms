#include <iostream>
#include <vector>

class SegmentTree {
 private:
  std::vector<int> segment_tree_;
  SegmentTree(std::vector<int>& origin) : segment_tree_(4 * segment_tree_.size()) {
    SegmentTree(origin, 1, 0, origin.size() - 1);
  }

 public:
  SegmentTree(std::vector<int>& origin, size_t node_index, size_t l_boundry, size_t r_boundry) {
    if (l_boundry == r_boundry) {
      segment_tree_[node_index] = origin[l_boundry];
    } else {
      int tm = (l_boundry + r_boundry) / 2;
      SegmentTree(origin, node_index * 2, l_boundry, tm);
      SegmentTree(origin, node_index * 2 + 1, tm + 1, r_boundry);
      segment_tree_[node_index] = segment_tree_[node_index * 2] + segment_tree_[node_index * 2 + 1];
    }
  }

  int sum(int node_index, int l_boundry, int r_boundry, int l, int r) {
    if (l > r)
      return 0;
    if (l == l_boundry && r == r_boundry)
      return segment_tree_[node_index];
    int tm = (l_boundry + r_boundry) / 2;
    return sum(node_index * 2, l_boundry, tm, l, std::min(r, tm)) +
           sum(node_index * 2 + 1, tm + 1, r_boundry, std::max(l, tm + 1), r);
  }

  void push(int node_index) {
    if (segment_tree_[node_index] != -1) {
      segment_tree_[node_index * 2] = segment_tree_[node_index * 2 + 1] = segment_tree_[node_index];
      segment_tree_[node_index] = -1;
    }
  }

  void update(int node_index, int l_boundry, int r_boundry, int l, int r, int color) {
    if (l > r)
      return;
    if (l == l_boundry && r_boundry == r)
      segment_tree_[node_index] = color;
    else {
      push(node_index);
      int tm = (l_boundry + r_boundry) / 2;
      update(node_index * 2, l_boundry, tm, l, std::min(r, tm), color);
      update(node_index * 2 + 1, tm + 1, r_boundry, std::max(l, tm + 1), r, color);
    }
  }

  int get(int node_index, int l_boundry, int r_boundry, int pos) {
    if (l_boundry == r_boundry)
      return segment_tree_[node_index];
    push(node_index);
    int tm = (l_boundry + r_boundry) / 2;
    if (pos <= tm)
      return get(node_index * 2, l_boundry, tm, pos);
    else
      return get(node_index * 2 + 1, tm + 1, r_boundry, pos);
  }
};
