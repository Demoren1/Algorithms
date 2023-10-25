#ifndef MERGE_GUARD
#define MERGE_GUARD

template <typename InputIterator1, typename InputIterator2, typename OutputIterator>
void Merge(InputIterator1 const* first_begin, InputIterator1 const* first_end, InputIterator2 const* second_begin,
           InputIterator2 const* second_end, OutputIterator* out) {
  while (first_begin != first_end && second_begin != second_end) {
    if (*first_begin < *second_begin) {
      *out = *first_begin;
      ++first_begin;
    } else {
      *out = *second_begin;
      ++second_begin;
    }
    ++out;
  }

  while (first_begin != first_end) {
    *out = *first_begin;
    ++first_begin;
    ++out;
  }

  while (second_begin != second_end) {
    *out = *second_begin;
    ++second_begin;
    ++out;
  }
}

#endif