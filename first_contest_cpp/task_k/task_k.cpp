#include <iostream>
#include <cstring>

int Solution(int64_t n, int64_t m, int64_t k);

int SumArrays(int64_t* dest, int64_t* src, int64_t shift, int64_t k);
int AnotherSolution(int64_t n, int64_t m, int64_t k);

int main() {
  std::ios_base::sync_with_stdio(false);

  int64_t n = 0;
  int64_t m = 0;
  int64_t k = 0;
  std::cin >> n >> m >> k;

  if (m % k > 1000) {
    AnotherSolution(n, m, k);
  } else {
    Solution(n, m, k);
  }

  return 0;
}

int Solution(int64_t n, int64_t m, int64_t k) {
  auto colors = new int64_t[k];
  auto vector_n = new int64_t[k];

  std::memset(colors, 0, k * sizeof(int64_t));
  std::memset(vector_n, 0, k * sizeof(int64_t));

  int64_t m_div_k = m / k;
  int64_t m_rem_k = m % k;
  if (k < m) {
    for (int i = 0; i < k; ++i) {
      colors[i] = n * (m_div_k);
    }
  }

  if (k < n) {
    int64_t tmp_n = n;
    for (int64_t i = 0; i < tmp_n; ++i) {
      if (i == k) {
        tmp_n = tmp_n - k;
        i = 0;
      }
      ++vector_n[i];
    }
  } else {
    for (int64_t i = 0; i < n; ++i) {
      ++vector_n[i];
    }
  }

  for (int shift = 0; shift < (m_rem_k); ++shift) {
    for (int i = 0; i < k - shift; ++i) {
      colors[i + shift] += vector_n[i];
    }

    for (int i = k - shift; i < k; ++i) {
      colors[i + shift - k] += vector_n[i];
    }
  }

  for (int64_t i = 0; i < k; ++i) {
    std::cout << colors[i] << ' ';
  }

  std::cout << '\n';

  delete[] colors;
  delete[] vector_n;
  return 0;
}

int SumArrays(int64_t* dest, int64_t* src, int64_t shift, int64_t k) {
  for (int i = 0; i < k - shift; ++i) {
    dest[i + shift] += src[i];
  }

  for (int i = k - shift; i < k; ++i) {
    dest[i + shift - k] += src[i];
  }

  return 0;
}

int AnotherSolution(int64_t n, int64_t m, int64_t k) {
  auto colors = new int64_t[k];
  std::memset(colors, 0, k * sizeof(int64_t));

  int global_color = 0;
  int color = 0;
  for (int64_t i = 0; i < m; ++i) {
    color = global_color;
    for (int64_t j = 0; j < n; ++j) {
      ++(colors[color]);
      ++color;
      if (color == k) {
        color = 0;
      }
    }
    ++global_color;
    if (global_color == k) {
      global_color = 0;
    }
  }

  for (int64_t color = 0; color < k; ++color) {
    if (color != k - 1) {
      std::cout << colors[color] << ' ';
    } else {
      std::cout << colors[color];
    }
  }

  delete[] colors;
  return 0;
}
