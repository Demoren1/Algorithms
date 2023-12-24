#include "string_view.h"
#include <algorithm>
#include <stdexcept>

StringView::StringView() : str_(nullptr), size_(0) {
}

StringView::StringView(const char* origin) {
  str_ = origin;
  const char *helper = str_;
  size_t size = 0;
  while (*helper != '\0')
  {
    helper++;
    size++;
  }
  size_ = size;

}

StringView::StringView(const char* origin, size_t origin_size) {
  str_ = origin;
  size_ = origin_size;
}

size_t StringView::Size() const {
  return size_;
}

const char& StringView::operator[](size_t index) const {
  return str_[index];
}

const char& StringView::Front() const {
  return str_[0];
}

const char& StringView::Back() const {
  return str_[size_ - 1];
}

size_t StringView::Length() const {
  size_t lenght = size_;

  return lenght;
}

bool StringView::Empty() const {
  return (0 == size_);
}

const char* StringView::Data() const {
  return str_;
}

int StringView::Swap(StringView& other) {
  StringView tmp_str = *this;
  *this = other;
  other = tmp_str;

  return 0;
}

int StringView::RemovePrefix(size_t prefix_size) {
  str_ += prefix_size;
  size_ -= prefix_size;

  return 0;
}

int StringView::RemoveSuffix(size_t suffix_size) {
  size_ -= suffix_size;

  return 0;
}

StringView StringView::Substr(size_t pos, size_t count = -1) const {
  size_t another_size = size_ - pos;
  size_t new_len = std::min(count, another_size);

  if (pos >= size_) {
    throw StringViewOutOfRange{};
    StringView result;
    return result;
  }

  StringView result(str_ + pos, new_len);
  return result;
}