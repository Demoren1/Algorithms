#include <iostream>
#include <deque>

struct DequeElem {
  int value;
  int position;
};

int Solution();

int FillArr(int* arr, int n);

int Push(std::deque<DequeElem>& deque, int elem);

class Window {
 private:
  std::deque<DequeElem> deque_;
  int l_boundry_ = 0;
  int r_boundry_ = 0;

 public:
  int Push(int elem) {
    while (!deque_.empty()) {
      if (deque_.back().value > elem) {
        deque_.pop_back();
      } else {
        deque_.push_back({elem, r_boundry_});
        break;
      }
    }
    if (deque_.empty()) {
      deque_.push_back({elem, r_boundry_});
    }

    ++r_boundry_;
    return 0;
  }

  int Pop() {
    ++l_boundry_;
    int result = deque_.front().value;
    if (deque_.front().position + 1 <= l_boundry_) {
      deque_.pop_front();
    }

    return result;
  }
  bool Empty() {
    return deque_.empty();
  }

  int ShowDeque() {
    printf("Deque: ");
    for (auto& elem : deque_) {
      printf("(%d, %d) ", elem.value, elem.position);
    }

    std::cout << '\n';

    printf("L = %d, R = %d \n", l_boundry_, r_boundry_);

    return 0;
  }
};

int main() {
  Solution();

  return 0;
}

int Solution() {
  int n = 0;
  int k = 0;

  std::cin >> n >> k;

  int* arr = new int[n];
  Window my_deque = {};

  FillArr(arr, n);

  for (int i = 0; i < k; ++i) {
    my_deque.Push(arr[i]);
  }

  for (int i = k; i < n; ++i) {
    std::cout << my_deque.Pop() << '\n';

    my_deque.Push(arr[i]);
  }
  std::cout << my_deque.Pop() << '\n';

  delete[] arr;

  return 0;
}

int FillArr(int* arr, int n) {
  int tmp_val = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> tmp_val;
    arr[i] = tmp_val;
  }

  return 0;
}
