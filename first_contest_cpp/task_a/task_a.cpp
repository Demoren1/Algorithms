#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstdio>

#define DBG printf("%s:%d -- %s\n", __FILE__, __LINE__, __FUNCTION__);

void Solution();
int FindDist(const std::vector<int>& arr, int len);
int FindNLines(const std::vector<int>& arr, int jump_dist, int len);
void ShowAnswer(int vert_dist, int hor_dist, int n_hor_lines, int n_vert_lines, int n_rows, int n_columns);

int main() {
  Solution();

  return 0;
}

void Solution() {
  int n_rows = 0;
  int n_columns = 0;

  int n_hor_lines = 0;
  int n_vert_lines = 0;

  int hor_dist = 0;
  int vert_dist = 0;

  std::cin >> n_rows >> n_columns;

  std::vector<std::vector<int>> rows(n_rows, std::vector<int>(n_columns));
  std::vector<std::vector<int>> columns(n_columns, std::vector<int>(n_rows));

  // int** rows = (int**) calloc(n_rows, sizeof(int*));
  // for (int i = 0; i < n_rows; ++i)
  // {
  //     rows[i] = (int*) calloc(n_columns, sizeof(int));
  // }

  // int** columns = (int**) calloc(n_columns, sizeof(int*));
  // for (int i = 0; i < n_columns; ++i)
  // {
  //     columns[i] = (int*) calloc(n_rows, sizeof(int));
  // }

  char tmp_val = 0;
  for (int i = 0; i < n_rows; ++i) {
    for (int j = 0; j < n_columns; ++j) {
      std::cin >> tmp_val;
      rows[i][j] = tmp_val - '0';
    }
  }

  for (int i = 0; i < n_columns; ++i) {
    for (int j = 0; j < n_rows; ++j) {
      columns[i][j] = rows[j][i];
    }
  }

  if (n_rows > 1) {
    hor_dist = std::max(FindDist(rows[0], n_columns), FindDist(rows[1], n_columns));
    n_vert_lines = std::max(FindNLines(rows[0], hor_dist, n_columns), FindNLines(rows[1], hor_dist, n_columns));
  } else {
    hor_dist = FindDist(rows[0], n_columns);
    n_vert_lines = FindNLines(rows[0], hor_dist, n_columns);
  }

  if (n_columns > 1) {
    vert_dist = std::max(FindDist(columns[0], n_rows), FindDist(columns[1], n_rows));
    n_hor_lines = std::max(FindNLines(columns[0], vert_dist, n_rows), FindNLines(columns[1], vert_dist, n_rows));
  } else {
    vert_dist = FindDist(columns[0], n_rows);
    n_hor_lines = FindNLines(columns[0], vert_dist, n_rows);
  }

  ShowAnswer(vert_dist, hor_dist, n_hor_lines, n_vert_lines, n_rows, n_columns);
}

int FindDist(const std::vector<int>& arr, int len) {
  int counter = 0;
  int result = 0;

  while (counter < len && arr[counter++] != 1) {
  }

  while (counter < len && arr[counter] != 1) {
    ++counter;
    ++result;
  }

  return result;
}

int FindNLines(const std::vector<int>& arr, int jump_dist, int len) {
  int n_lines = 0;
  int counter = 0;

  if (len > 1) {
    if (arr[0] == 1 && arr[1] == 1) {
      return 0;
    }
  }

  while (counter < len && arr[counter] == 0) {
    ++counter;
  }

  while (counter < len) {
    if (arr[counter] == 1) {
      ++n_lines;
    } else {
      return -1;
    }
    counter += jump_dist + 1;
  }

  return n_lines;
}

void ShowAnswer(int vert_dist, int hor_dist, int n_hor_lines, int n_vert_lines, int n_rows, int n_columns) {
  if (n_vert_lines > 0 && n_hor_lines > 0) {
    std::cout << "Square";
  } else if (n_vert_lines > 0) {
    if (n_vert_lines == 1) {
      std::cout << "?";
    } else if (hor_dist >= n_rows) {
      std::cout << "?";
    } else {
      std::cout << "Vertical line";
    }
  } else if (n_hor_lines > 0) {
    if (n_hor_lines == 1) {
      std::cout << "?";
    } else if (vert_dist >= n_columns) {
      std::cout << "?";
    } else {
      std::cout << "Line";
    }
  } else if (n_rows == 1 || n_columns == 1) {
    std::cout << "?";
  }
}
