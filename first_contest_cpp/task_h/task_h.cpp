#include <iostream>

template <typename Iterator>
Iterator* Partition(Iterator* begin, Iterator* end) {
  Iterator* pivot = end - 1;
  Iterator* i = begin;

  for (Iterator* j = begin; j < end - 1; ++j) {
    if (*j < *pivot) {
      std::swap(*i, *j);
      ++i;
    }
  }

  std::swap(*i, *pivot);
  return i;
}

template <typename Iterator>
void KthElement(Iterator* begin, Iterator* kth, Iterator* end) {
  if (begin < end) {
    Iterator* pivot = Partition(begin, end);

    if (kth < pivot) {
      KthElement(begin, kth, pivot);
    } else if (kth > pivot) {
      KthElement(pivot + 1, kth, end);
    }
  }
}

int main() {
  int array[5]{2, 3, 5, 4, 1};
  KthElement(array, array + 2, array + 5);

  for (int i = 0; i < 5; ++i) {
    std::cout << array[i] << " ";
  }

  return 0;
}
