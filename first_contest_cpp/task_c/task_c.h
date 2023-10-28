#ifndef TASK_C_H
#define TASK_C_H

template <typename Iter>
void Sort(Iter* begin, Iter* end) {
  int l_index = 0;
  int r_index = end - begin - 1;
  int size = end - begin;

  Iter mid = begin[size / 2];

  do {
    while (begin[l_index] < mid) {
      l_index++;
    }
    while (mid < begin[r_index]) {
      r_index--;
    }

    if (l_index <= r_index) {
      Iter tmp = begin[l_index];
      begin[l_index] = begin[r_index];
      begin[r_index] = tmp;

      l_index++;
      r_index--;
    }
  } while (l_index <= r_index);

  if (r_index > 0) {
    Sort(begin, begin + r_index + 1);
  }
  if (l_index < size) {
    Sort(begin + l_index, begin + size);
  }
}

#endif