#include <vector>
#include <iostream>
#include <algorithm>

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

void qsortRecursive(int *mas, int size) {
    int i = 0;
    int j = size - 1;
    int mid = mas[size / 2];

    do {
        while(mas[i] < mid) {
            i++;
        }
        while(mas[j] > mid) {
            j--;
        }

        if (i <= j) {
            int tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);


    if(j > 0) {
        printf("in first if j+1 = %d\n", j + 1);
        qsortRecursive(mas, j + 1);
    }
    if (i < size) {
        printf("in second if size - i = %d", size - i);

        qsortRecursive(mas + i, size - i);
    }
}

int main() {
  int a[5] = {5, 2, 3, 1, 4};

  Sort(a, a + 5);
  // qsortRecursive(a, 5);

  for (int r_index = 0; r_index < 5; ++r_index)
    std::cout << a[r_index] << '\n';
}
