#include <iostream>
#include <vector>

int get_sum(int start, int finish, const std::vector<int>& prefix_sums) {
  int sum = prefix_sums[finish];
  if (start > 0) {
    sum -= prefix_sums[start - 1];
  }
  return sum;
}

int main() {

  std::ios_base::sync_with_stdio(false);
  
  size_t N;
  std::cin >> N;
  std::vector<int> prefix_sums(N + 1, 0);

  int score;
  std::cin >> score;

  prefix_sums[1] = score;

  for (size_t i = 2; i <= N; ++i) {
    std::cin >> score;

    prefix_sums[i] += prefix_sums[i - 1] + score;
  }

  int K = 0;
  std::cin >> K;

  for (int i = 0; i != K; ++i) {
    int start, finish;
    std::cin >> start >> finish;
    std::cout << get_sum(start, finish, prefix_sums) << std::endl;
  }

  return 0;
}