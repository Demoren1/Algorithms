#include <iostream>
#include <array>

template <typename T, size_t N>
class Array {
 public:
  T array[N] = {};

  Array() = default;

  Array(const Array& other) {
    std::copy(other.array, other.array + N, this->array);
  }

  Array(std::initializer_list<T> init_list) {
    
    size_t size = std::min(init_list.size(), N);
    std::copy(init_list.begin(), init_list.begin() + size, this->array);
  }

  Array(Array&& other) noexcept {
    std::move(other.array, other.array + N, this->array);
  }

  Array& operator=(Array& other) {
    std::move(other.array, other.array + N, this->array);

    return *this;
  }

  Array& operator=(const Array& other) {
    std::move(other.array, other.array + N, this->array);

    return *this;
  }

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
    for (int i = 0; i < N; ++i) {
      array[i] = value;
    }

    return 0;
  }

  int Swap(Array& other) {
    for (int i = 0; i < N; ++i) {
      std::swap(array[i], other.array[i]);
    }

    return 0;
  }

  void ShowArr() const {
    for (int i = 0; i < N; ++i) {
      std::cout << array[i] << '\n';
    }
  }

  ~Array() = default;
};


template <typename T, size_t N>
void show_arr(std::array<T, N> arr);


int main()
{

  // std::array<int, 5> test_arr = {1, 2, 3, 4, 5};

  // std::array test_arr = {1, 2, 3, 4, 5};

  // Array<int, 5> test_arr {1, 2, 3, 4, 5};
  Array<int, 5> my_arr{6, 7, 8};
  my_arr.ShowArr();

  // printf("true = %d, mine = %d\n", test_arr[5], my_arr[5]);

  return 0;
}


template <typename T, size_t N>
void show_arr(std::array<T, N> arr)
{
  for (int i = 0; i < N; ++i)
      {
        std::cout << arr[i] << '\n';
      }
}