#include <iostream>
#include <cstring>

int Solution();

int** Ctor2DArray(int n);

void Dtor2DArray(int** arr, int n);

void FormAnswer(int** arr, int* ans, int n);

void ShowAns(int* ans, int n);

bool CheckSol(int** arr, int* ans, int n);

// #define DBG printf("%s:%d -- %s\n", __FILE__, __LINE__, __FUNCTION__);

int main() {

  Solution();

  return 0;
}

int Solution() {
  int n = 0;
  std::cin >> n;

  auto arr = Ctor2DArray(n);
  auto ans = new int[n];

  int tmp_num = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> tmp_num;
      arr[i][j] = tmp_num;
    }
  }

  FormAnswer(arr, ans, n);

  if (CheckSol(arr, ans, n)) {
    ShowAns(ans, n);
  } else {
    std::cout << -1 << '\n';
  }

  delete[] ans;
  Dtor2DArray(arr, n);

  return 0;
}

int** Ctor2DArray(int n) {
  auto arr = new int*[n];

  for (int i = 0; i < n; ++i) {
    arr[i] = new int[n];
    std::memset(arr[i], 0, n * sizeof(int));
  }

  return arr;
}

void Dtor2DArray(int** arr, int n) {
  for (int i = 0; i < n; ++i) {
    delete[] arr[i];
  }

  delete[] arr;
}

void FormAnswer(int** arr, int* ans, int n) {

  int tmp_num = 0;
  for (int i = 0; i < n; ++i) {
    tmp_num = 9999;
    for (int j = 0; j < n; ++j) {
      if (i == j) {
        continue;
      }
      tmp_num = std::min(tmp_num, arr[i][j]);
    }
    ans[i] = tmp_num;
  }

  if (n == 1) {
    ans[0] = 0;
  }
}

void ShowAns(int* ans, int n) {
  for (int i = 0; i < n; ++i) {
    std::cout << ans[i] << ' ';
  }

  std::cout << '\n';
}

bool CheckSol(int** arr, int* ans, int n) {
  for (int i = 0; i < n; ++i) {
    if (arr[i][i] != 0) {
      return false;
    }
    for (int j = 0; j < n; ++j) {
      if (i != j && (arr[i][j] != arr[j][i] || arr[i][j] < 1)) {
        return false;
      }
      if ((i != j) && arr[i][j] != std::max(ans[i], ans[j])) {
        return false;
      }
    }
  }

  return true;
}