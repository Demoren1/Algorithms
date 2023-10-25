#include <iostream>

template <class T>
bool BinarySearch(T const* begin, T const* end, T const& value) {
  while (begin <= end) {
    T const* mid = begin + (end - begin) / 2;

    if (!(*mid < value || value < *mid)) {
      return true;
    } else if (*mid < value) {
      begin = mid + 1;
    } else {
      end = mid - 1;
    }
  }

  return false;
}

template <class T>
T const* LowerBound(T const* begin, T const* end, T const& value) {
  int l_index = 0;
  int r_index = end - begin;
  while (l_index < r_index)
  {
    int mid = l_index + (r_index - l_index) / 2;
    if (value <= begin[mid])
    {
      r_index = mid;
    }
    else
    {
      l_index = mid + 1;
    }
  }

  return (begin + l_index);
}

template <class T>
T const* UpperBound(T const* begin, T const* end, T const& value) {
  int l_index = 0;
  int r_index = end - begin;
  while (l_index < r_index)
  {
    int mid = l_index + (r_index - l_index) / 2;
    if (value >= begin[mid])
    {
      l_index = mid + 1;
    }
    else
    {
      r_index = mid;
    }
  }

  return (begin + l_index);
}


int main()
{
  int array[5]{1, 2, 3, 4, 5};


  // LowerBound(array, array + 5, 10);
  std::cout << BinarySearch(array, array + 4, 2) << '\n';
  std::cout << *LowerBound(array + 1, array + 5, 3) << '\n';
  std::cout << *UpperBound(array, array + 2, 4) << '\n';
}