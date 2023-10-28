#include <iostream>
#include <cstring>
#include <algorithm>

int Solution(int64_t n, int64_t m, int64_t k);

int SumArrays(int64_t* dest, int64_t* src, int64_t shift, int64_t k);

int64_t GetSum(int64_t* colors, int64_t k);

int ShowColors(int64_t* colors, int k);

void SolveGeneralWay(int64_t m, int64_t n, int64_t k, int64_t* vector_rem_n, int64_t* colors);

int main() {
  int64_t n = 0;
  int64_t m = 0;
  int64_t k = 0;
  std::cin >> n >> m >> k;
  Solution(n, m, k);

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

  for (int i = 0; i < k; ++i) {
    colors[i] += m * n_div_k;
  }

  for (int i = 0; i < k; ++i) {
    colors[i] += n_rem_k * m_div_k;
  }

  for (int64_t i = 0; i < n_rem_k; ++i) {
    ++vector_rem_n[i];
  }

  if (m_rem_k > 0 && n_rem_k > 0) {
    SolveGeneralWay(m, n, k, vector_rem_n, colors);
  }

  ShowColors(colors, k);

  int result = (checkable_mult == GetSum(colors, k));

  delete[] colors;
  delete[] vector_div_n;
  delete[] vector_rem_n;

  return result;
}

void SolveGeneralWay(int64_t m, int64_t n, int64_t k, int64_t* vector_rem_n, int64_t* colors) {
  int64_t m_rem_k = m % k;
  int64_t n_rem_k = n % k;

  m = m_rem_k - 1;
  for (int i = 0; i < k; ++i) {
    int dist = i - (n_rem_k - 1) - 1;

    if (dist >= 0) {
      if (m - dist >= n_rem_k) {
        vector_rem_n[i] += n_rem_k;
      } else if (m - dist > 0) {
        vector_rem_n[i] += m - dist;
      }
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
    }
  }

  for (int64_t i = 0; i < k; ++i) {
    colors[i] += vector_rem_n[i];
  }
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
