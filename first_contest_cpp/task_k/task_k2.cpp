#include <iostream>
#include <cstring>
#include <algorithm>

#define DBG printf("%s:%d -- %s\n", __FILE__, __LINE__, __FUNCTION__);

int Solution(int64_t n, int64_t m, int64_t k);

int SumArrays(int64_t* dest, int64_t* src, int64_t shift, int64_t k);

int64_t GetSum(int64_t* colors, int64_t k);

int ShowColors(int64_t* colors, int k);

int main() {
  // std::ios_base::sync_with_stdio(false);

  int64_t n = 0;
  int64_t m = 0;
  int64_t k = 0;
  std::cin >> n >> m >> k;
  Solution(n, m, k);

  // for (int64_t k = 2; k < 10; ++k) {
  //   for (int64_t n = 0; n < 10; ++n) {
  //     for (int64_t m = 0; m < 10; ++m){
  //       int result = Solution(n, m, k);
  //       printf("n: %ld, m: %ld, k: %ld, solution = %d\n", n, m, k, result);
  //       // Solution(n, m, k);
  //     }
  //   }
  // }

  return 0;
}

int Solution(int64_t n, int64_t m, int64_t k) {
  auto colors = new int64_t[k];
  auto vector_div_n = new int64_t[k];
  auto vector_rem_n = new int64_t[k];

  std::memset(colors, 0, k * sizeof(int64_t));
  std::memset(vector_div_n, 0, k * sizeof(int64_t));
  std::memset(vector_rem_n, 0, k * sizeof(int64_t));

  int64_t m_div_k = m / k;
  int64_t m_rem_k = m % k;
  int64_t n_div_k = n / k;
  int64_t n_rem_k = n % k;
  int64_t checkable_mult = m * n;

  // if (n_rem_k == 0) {
  //   for (int64_t i = 0; i < k; ++i) {
  //     colors[i] += m * n_div_k;
  //   }
  // }
  // else {
  //   for (int i = 0; i < k; ++i) {
  //     colors[i] = n * m_div_k;
  //   }
  // }

  // ShowColors(colors, k);

  for (int i = 0; i < k; ++i) {
    colors[i] += m * n_div_k;
  }

  for (int i = 0; i < k; ++i) {
    colors[i] += n_rem_k * m_div_k;
  }

  // ShowColors(colors, k);

  for (int64_t i = 0; i < n_rem_k; ++i) {
    ++vector_rem_n[i];
  }

  if (m_rem_k > 0 && n_rem_k > 0) {
    m = m_rem_k - 1;
    for (int i = 0; i < k; ++i) {
      int dist = i - (n_rem_k - 1) - 1;

      if (dist >= 0) {
        if (m - dist >= n_rem_k) {
          vector_rem_n[i] += n_rem_k;
        } else if (m - dist > 0) {
          vector_rem_n[i] += m - dist;
        }
        // printf("i = %d, m - dist = %ld\n", i, m - dist);
        // ShowColors(colors, k);
      }

      if (dist < 0) {
        int64_t other_dist = k - (n_rem_k - 1) + i - 1;

        if (other_dist >= 0) {
          if (m - other_dist >= n_rem_k) {
            vector_rem_n[i] += n_rem_k;
          } else if (m - other_dist > 0) {
            vector_rem_n[i] += m - other_dist;
          }
        }
        if (m >= i && m > 0) {
          vector_rem_n[i] += i;
        } else if (m < i && m > 0) {
          vector_rem_n[i] += m;
        }
        // printf("i = %d, other_dist = %ld\n", i, other_dist);
        // ShowColors(colors, k);
      }
    }

    for (int64_t i = 0; i < k; ++i) {
      colors[i] += vector_rem_n[i];
    }
  }

  ShowColors(colors, k);

  int result = (checkable_mult == GetSum(colors, k));

  delete[] colors;
  delete[] vector_div_n;
  delete[] vector_rem_n;

  return result;
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

int ShowColors(int64_t* colors, int k) {
  for (int64_t i = 0; i < k; ++i) {
    std::cout << colors[i] << ' ';
  }

  std::cout << '\n';

  return 0;
}

int64_t GetSum(int64_t* colors, int64_t k) {
  int64_t result = 0;

  for (int i = 0; i < k; ++i) {
    result += colors[i];
  }

  return result;
}
