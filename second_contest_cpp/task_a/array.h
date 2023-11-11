#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <algorithm>

template <typename T, size_t N>
class Array {
 public:
  T array[N] = {};

  size_t Size() const {
    return N;
  }

  T& operator[](size_t index) {
    return array[index];
  }

  const T& operator[](size_t index) const {
    return array[index];
  }

  const T* Data() const {
    return array;
  }

  T* Data() {
    return array;
  }

  bool Empty() const {
    return N == 0;
  }

  T& Front() {
    return array[0];
  }

  const T& Front() const {
    return array[0];
  }

  T& Back() {
    if (this->Empty()) {
      return array[0];
    }

    return array[N - 1];
  }

  const T& Back() const {
    if (this->Empty()) {
      return array[0];
    }

    return array[N - 1];
  }

  int Fill(const T& value) {
    for (size_t i = 0; i < N; ++i) {
      array[i] = value;
    }

    return 0;
  }

  int Swap(Array& other) {
    for (size_t i = 0; i < N; ++i) {
      std::swap(array[i], other.array[i]);
    }

    return 0;
  }

  void ShowArr() const {
    for (size_t i = 0; i < N; ++i) {
      std::cout << array[i] << '\n';
    }
  }
};

#endif