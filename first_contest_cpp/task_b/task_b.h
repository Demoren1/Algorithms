#ifndef TASK_B_H
#define TASK_B_H

template <class T>
T const* LowerBound(T const* begin, T const* end, T const& value) {
  int l_index = 0;
  int r_index = end - begin;
  while (l_index < r_index) {
    int mid = l_index + (r_index - l_index) / 2;
    if (value < begin[mid] || !(value < begin[mid] || begin[mid] < value)) {
      r_index = mid;
    } else {
      l_index = mid + 1;
    }
  }

  return (begin + l_index);
}

template <class T>
T const* UpperBound(T const* begin, T const* end, T const& value) {
  int l_index = 0;
  int r_index = end - begin;
  while (l_index < r_index) {
    int mid = l_index + (r_index - l_index) / 2;
    if (begin[mid] < value || !(value < begin[mid] || begin[mid] < value)) {
      l_index = mid + 1;
    } else {
      r_index = mid;
    }
  }

  return (begin + l_index);
}

template <class T>
bool BinarySearch(T const* begin, T const* end, T const& value) {
  begin = LowerBound(begin, end, value);

  return (!(begin == end) && !(value < *begin));
}

#endif