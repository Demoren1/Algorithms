#ifndef HEAPSORT
#define HEAPSORT

template <class T>
void Swap(T &a, T &b)
{
  T temp = a;
  a = b;
  b = temp;
}
int LeftChild(int i)
{
  return 2 * i + 1;
}
int RightChild(int i)
{
  return 2 * i + 2;
}
template <class T>
void SiftDown(T *arr, int i, int size)
{
  int left = LeftChild(i);
  int right = RightChild(i);
  int largest = i;

  if (left < size && arr[largest] < arr[left])
  {
    largest = left;
  }
  if (right < size && arr[largest] < arr[right])
  {
    largest = right;
  }

  if (largest != i)
  {
    Swap(arr[i], arr[largest]);
    SiftDown(arr, largest, size);
  }
}
template <class T>
void MakeHeap(T *begin, T *end)
{
  int size = end - begin;
  for (int i = (size - 1) / 2; i >= 0; i--)
  {
    SiftDown(begin, i, size);
  }
}
template <class T>
void SortHeap(T *begin, T *end)
{
  int size = end - begin;
  MakeHeap(begin, end);
  for (int i = size - 1; i > 0; i--)
  {
    Swap(begin[0], begin[i]);
    --size;
    SiftDown(begin, 0, size);
  }
}

#endif