#ifndef STRING_VIEW_H
#define STRING_VIEW_H
#include <stdexcept>

class StringViewOutOfRange : public std::out_of_range {
 public:
  StringViewOutOfRange() : std::out_of_range("Index out of range") {
  }
};

class StringView {
 private:
  const char* str_ = nullptr;
  size_t size_ = 0;

 public:
  StringView();

  StringView(const char* origin);  // NOLINT

  StringView(const char* origin, size_t origin_size);

  const char& operator[](size_t index) const;

  const char& Front() const;

  const char& Back() const;

  size_t Length() const;

  bool Empty() const;

  const char* Data() const;

  int Swap(StringView& other);

  int RemovePrefix(size_t prefix_size);

  int RemoveSuffix(size_t suffix_size);

  StringView Substr(size_t pos, size_t count) const;

  size_t Size() const;
};

#endif