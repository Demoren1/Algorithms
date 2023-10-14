#include <iostream>

void FindWidthAndVert(int* array, int n, int m, int& vert, int& width) {
  if (n > 1) {
    int helper = -1;
    for (int i = 0; i < m; ++i) {
      if (array[i] == 1 && array[i + m] == 1) {
        if (helper != -1) {
          width = i - helper - 1;
        }
        helper = i;
        ++vert;
      }
    }
  }
}

void FindHeightAndHori(int* array, int n, int m, int& hori, int& height) {
  if (m > 1) {
    int helper = -1;
    for (int i = 0; i < n * m; i += m) {
      if (array[i] == 1 && array[i + 1] == 1) {
        if (helper != -1) {
          height = i / m - helper - 1;
        }
        helper = i / m;
        ++hori;
      }
    }
  }
}

void MakeAnswer(int vert, int hori, int width, int height, int n, int m) {
  if (vert > 0 && hori > 0) {
    std::cout << "Square";
  } else if (vert > 0) {
    if (vert == 1) {
      std::cout << "?";
    } else if (width >= n) {
      std::cout << "?";
    } else {
      std::cout << "Vertical line";
    }
  } else if (hori > 0) {
    if (hori == 1) {
      std::cout << "?";
    } else if (height >= m) {
      std::cout << "?";
    } else {
      std::cout << "Line";
    }
  } else if (n == 1 || m == 1) {
    std::cout << "?";
  }
}

int main() {
  int vert = 0;
  int hori = 0;
  int width;
  int height;

  int n;
  int m;
  std::cin >> n >> m;
  auto* array = new int[n * m];
  for (int i = 0; i < n * m; ++i) {
    char simvol;
    std::cin >> simvol;
    array[i] = static_cast<int>(simvol) / '1';
  }

  FindWidthAndVert(array, n, m, vert, width);
  FindHeightAndHori(array, n, m, hori, height);

  MakeAnswer(vert, hori, width, height, n, m);

  delete[] array;
}