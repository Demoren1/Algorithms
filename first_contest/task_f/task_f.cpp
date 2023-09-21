#include <iostream>
#include <vector>

template <typename T>
class Fenvic {
 private:
  std::vector<std::vector<std::vector<T>>> fenvic_tree_;
  size_t original_size_;

 public:
  explicit Fenvic(const int n_size) : original_size_(n_size) {
    fenvic_tree_.resize(n_size, std::vector<std::vector<T>>(n_size, std::vector<T>(n_size, 0)));
  }

  void Update(int x, int y, int z, const T& delta) {
    for (size_t i = x; i < original_size_; i = i | (i + 1)) {
      for (size_t j = y; j < original_size_; j = j | (j + 1)) {
        for (size_t k = z; k < original_size_; k = k | (k + 1)) {
          // printf("i= %ld j= %ld k= %ld", i, j, k);
          fenvic_tree_[i][j][k] += delta;
        }
      }
    }
  }

  const T Sum(int x1, int y1, int z1) {
    T sum = 0;
    if (x1 < 0 || y1 < 0 || z1 < 0) {
      return 0;
    }

    for (int i = x1; i >= 0; i = (i & (i + 1)) - 1) {
      for (int j = y1; j >= 0; j = (j & (j + 1)) - 1) {
        for (int k = z1; k >= 0; k = (k & (k + 1)) - 1) {
          sum += fenvic_tree_[i][j][k];
        }
      }
    }

    return sum;
  }

  const T Sum(int x1, int y1, int z1, int x2, int y2, int z2) {
    return Sum(x2, y2, z2) - Sum(x1 - 1, y2, z2) - Sum(x2, y1 - 1, z2) - Sum(x2, y2, z1 - 1) + Sum(x1 - 1, y1 - 1, z2) +
           Sum(x2, y1 - 1, z1 - 1) + Sum(x1 - 1, y2, z1 - 1) - Sum(x1 - 1, y1 - 1, z1 - 1);
  }

  void ShowCube() {
    for (size_t i = 0; i < original_size_; ++i) {
      printf("%ld slice \n", i);
      for (size_t j = 0; j < original_size_; ++j) {
        for (size_t k = 0; k < original_size_; ++k) {
          std::cout << fenvic_tree_[i][j][k] << ' ';
        }
        std::cout << '\n';
      }
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  int managing_num = 0;

  std::cin >> n;
  Fenvic<int> fenvic(n);

  int x1 = 0;
  int y1 = 0;
  int z1 = 0;
  int x2 = 0;
  int y2 = 0;
  int z2 = 0;
  int tmp = 0;

  while (managing_num != 3) {
    std::cin >> managing_num;
    switch (managing_num) {
      case 1: {
        std::cin >> x1 >> y1 >> z1 >> tmp;
        fenvic.Update(x1, y1, z1, tmp);
        // fenvic.show_cube();
        break;
      }
      case 2: {
        std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
        std::cout << fenvic.Sum(x1, y1, z1, x2, y2, z2) << '\n';
        break;
      }
    }
  }
  return 0;
}
