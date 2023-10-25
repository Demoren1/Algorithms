#include <iostream>

template <typename InputIterator1, typename InputIterator2, typename OutputIterator>
void Merge(InputIterator1* first_begin, InputIterator1* first_end, InputIterator2* second_begin,
           InputIterator2* second_end, OutputIterator* out) {
  while (first_begin != first_end && second_begin != second_end) {
    if (*first_begin < *second_begin) {
      *out = *first_begin;
      ++first_begin;
    } else {
      *out = *second_begin;
      ++second_begin;
    }
    ++out;
  }

  while (first_begin != first_end) {
    *out = *first_begin;
    ++first_begin;
    ++out;
  }

  while (second_begin != second_end) {
    *out = *second_begin;
    ++second_begin;
    ++out;
  }
}

int main() {
  int first[] = {1, 3, 5, 7, 9};
  int second[] = {2, 4, 6, 8, 10};
  int merged[10];

  Merge(first, first + 5, second, second + 5, merged);

  for (int i = 0; i < 10; ++i) {
    std::cout << merged[i] << " ";
  }

  return 0;
}
