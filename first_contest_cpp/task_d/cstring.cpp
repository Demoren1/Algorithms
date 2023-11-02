#include <iostream>
#include <cstring>

size_t Strlen(const char* str) {
  size_t len = 0;

  while (*str != '\0') {
    ++len;
    ++str;
  }

  return len;
}

int Strncmp(const char* first, const char* second, size_t count) {
  size_t counter = 0;

  size_t first_len = Strlen(first) + 1;
  size_t second_len = Strlen(second) + 1;

  if (first_len < count && second_len < count) {
    if (first_len != second_len) {
      if (first_len < second_len) {
        return second_len - first_len;
      }
      return first_len - second_len;
    }
  }
  if ((first_len < count && second_len >= count) || (first_len >= count && second_len < count)) {
    return first_len - second_len;
  }

  while (counter < count && counter < first_len && *first == *second) {
    ++counter;
    ++first;
    ++second;
  }

  if (counter == first_len || counter == count) {
    return 0;
  }

  return *first - *second;
}

int Strcmp(const char* first, const char* second) {
  size_t count = std::max(Strlen(first), Strlen(second));
  return Strncmp(first, second, count);
}

char* Strncpy(char* dest, const char* src, size_t count) {
  size_t src_len = Strlen(src) + 1;
  size_t counter = 0;

  while (counter < count && counter < src_len) {
    *dest = *src;
    ++counter;
    ++src;
    ++dest;
  }

  while (counter < count) {
    *dest = 0;
    ++dest;
    ++counter;
  }

  return dest - counter;
}

char* Strcpy(char* dest, const char* src) {
  size_t count = Strlen(src) + 1;
  return Strncpy(dest, src, count);
}

char* Strncat(char* dest, const char* src, size_t count) {
  size_t src_len = Strlen(src);
  size_t dest_len = Strlen(dest);
  size_t counter = 0;

  char* dest_to_ret = dest;
  dest += dest_len;

  while (counter < count && counter < src_len) {
    *dest = *src;
    ++dest;
    ++src;
    ++counter;
  }

  return dest_to_ret;
}

char* Strcat(char* dest, const char* src) {
  size_t count = Strlen(src);

  return Strncat(dest, src, count);
}

const char* Strchr(const char* str, char symbol) {
  size_t src_len = Strlen(str) + 1;
  size_t counter = 0;

  while (counter < src_len && *str != symbol) {
    ++str;
    ++counter;
  }

  if (counter == src_len) {
    return nullptr;
  }

  return str;
}

const char* Strrchr(const char* str, char symbol) {
  size_t src_len = Strlen(str) + 1;
  size_t counter = 0;
  str += src_len - 1;

  while (counter < src_len && *str != symbol) {
    --str;
    ++counter;
  }

  if (counter == src_len) {
    return nullptr;
  }

  return str;
}

size_t Strspn(const char* dest, const char* src) {
  size_t count = Strlen(dest);
  size_t counter = 0;

  while (counter < count && Strchr(src, *dest) != nullptr) {
    ++counter;
    ++dest;
  }

  return counter;
}

size_t Strcspn(const char* dest, const char* src) {
  size_t count = Strlen(dest);
  size_t counter = 0;

  while (counter < count && Strchr(src, *dest) == nullptr) {
    ++counter;
    ++dest;
  }

  return counter;
}

const char* Strpbrk(const char* dest, const char* breakset) {
  size_t count = Strlen(dest);
  size_t counter = 0;

  while (counter < count && Strchr(breakset, *dest) == nullptr) {
    ++counter;
    ++dest;
  }

  if (counter == count) {
    return nullptr;
  }

  return dest;
}

const char* Strstr(const char* str, const char* pattern) {
  if (Strlen(pattern) == 0) {
    return str;
  }

  if (str == nullptr || pattern == nullptr) {
    return nullptr;
  }

  const char* first_str = nullptr;
  const char* second_str = nullptr;

  while (*str != '\0') {
    if (*str == *pattern) {
      first_str = str;
      second_str = pattern;

      while (*first_str && *second_str) {
        if (*first_str != *second_str) {
          break;
        }

        first_str++;
        second_str++;
      }

      if (*second_str == '\0') {
        return str;
      }
    }

    str++;
  }

  return nullptr;
}
