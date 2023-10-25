#include <iostream>
#include <cstring>

int Solution(int n, int m, int k);

int main() {

  for (int k = 2; k < 10; ++k) {
    for (int n = 0; n < 10; ++n) {
      for (int m = 0; m < 10; ++m){
        printf(" k: %d , n: %d, m: %d\n", k, n, m);
        Solution(n, m, k);
      }
    }
  }

  return 0;
}

int Solution(int n, int m, int k) {
  // std::cin >> n >> m >> k;

  auto table = new int *[n];
  for (int i = 0; i < n; ++i) {
    table[i] = new int[m];
    std::memset(table[i], 0, m * sizeof(int));
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int color = (i + j) % k;
      table[i][j] = color;
    }
  }

  // for (int i = 0; i < n; ++i) {
  //   for (int j = 0; j < m; ++j) {
  //     std::cout << table[i][j] << ' ';
  //   }
  //   std::cout << '\n';
  // }

  // std::cout << '\n';

  int result = 0;
  for (int color = 0; color < k; ++color) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (table[i][j] == color) {
          ++result;
        }
      }
    }
    if (color != k - 1) {
      std::cout << result << ' ';
    } else {
      std::cout << result;
    }
    result = 0;
  }

  std::cout << '\n';

  for (int i = 0; i < n; ++i) {
    delete[] table[i];
  }
  delete[] table;
  return 0;
}