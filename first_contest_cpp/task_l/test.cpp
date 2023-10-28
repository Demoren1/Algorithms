#include <iostream>

bool Solve(int *arr, int n, int *ans) {
  for (int i = 0; i < n; i++) {

    int mn = 1000 + 1;

    for (int j = 0; j < n; j++) {

      if (i == j) 
      {
        if (arr[i * n + j] != 0) 
        {
          return false;
        }
        continue;
      }

      if (arr[i * n + j] != arr[j * n + i] || arr[i * n + j] < 1) 
      {
        return false;
      }

      if (arr[i * n + j] < mn) 
      {
        mn = arr[i * n + j];
      }
    }
    
    ans[i] = mn;
  }
  return true;
}

int Max(int a, int b) {
  return (a > b ? a : b);
}

bool Check(int *ans, int *arr, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j && arr[i * n + j] != Max(ans[i], ans[j])) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  int n;
  std::cin >> n;
  auto *arr = new int[n * n];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> arr[i * n + j];
    }
  }
  auto *ans = new int[n];
  if (Solve(arr, n, ans) && Check(ans, arr, n)) {
    for (int i = 0; i < n; i++) {
      std::cout << ans[i] << " ";
    }
  } else {
    std::cout << -1;
  }
  delete[] ans;
  delete[] arr;
}