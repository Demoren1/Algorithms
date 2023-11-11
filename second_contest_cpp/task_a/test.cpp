#include <iostream>


template <typename T, size_t N>
class Array {
 public:
  T arr[N];
  size_t Size() const {
    return N;
  }
  bool Empty() const {
    return (Size() == 0);
  }
  T& operator[](size_t idx) {
    return arr[idx];
  }
  const T& operator[](size_t idx) const {
    return arr[idx];
  }
  T& At(size_t idx) {
    if (idx >= N) {
      throw ArrayOutOfRange{};
    } else {
      return arr[idx];
    }
  }
  const T& At(size_t idx) const {
    if (idx >= N) {
      throw ArrayOutOfRange{};
    } else {
      return arr[idx];
    }
  }
  T& Front() {
    return arr[0];
  }
  const T& Front() const {
    return arr[0];
  }
  T& Back() {
    if (N > 0) {
      return arr[N - 1];
    }
    return arr[N];
  }
  const T& Back() const {
    if (N > 0) {
      return arr[N - 1];
    }
    return arr[N];
  }
  T* Data() {
    return &arr[0];
  }
  const T* Data() const {
    return &arr[0];
  }
  void Fill(const T& value) {
    T* p = arr;
    for (size_t i = 0; i < Size(); i++) {
      *p++ = value;
    }
  }
  void Swap(Array<T, N>& other) {
    T* first = Data();
    T* second = other.Data();
    for (size_t i = 0; i < Size(); i++) {
      T temp = *first;
      *first = *second;
      *second = temp;
      first++;
      second++;
    }
  }
};

