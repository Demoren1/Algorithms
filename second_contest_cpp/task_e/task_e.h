#ifndef TASK_E_H
#define TASK_E_H

#include <utility>

template <class T>
void SiftDown(T *arr, int index, int size) {
  int left = 2 * index + 1;
  int right = 2 * index + 2;
  int largest = index;

  if (left < size && arr[largest] < arr[left]) {
    largest = left;
  }
  if (right < size && arr[largest] < arr[right]) {
    largest = right;
  }

  if (largest != index) {
    std::swap(arr[index], arr[largest]);
    SiftDown(arr, largest, size);
  }
}

template <class T>
void MakeHeap(T *begin, T *end) {
  int size = end - begin;

  for (int i = (size - 1) / 2; i >= 0; --i) {
    SiftDown(begin, i, size);
  }
}

template <class T>
void SortHeap(T *begin, T *end) {
  int size = end - begin;

  MakeHeap(begin, end);
  for (int i = size - 1; i > 0; i--) {
    std::swap(begin[0], begin[i]);
    --size;
    SiftDown(begin, 0, size);
  }
}

#endif