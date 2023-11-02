#include <iostream>
#include <cstring>

class Table {
 private:
  int **table_;
  int n_;

 public:
  int **GetTable() {
    return table_;
  }

  int GetN() {
    return n_;
  }

  Table &operator=(Table &) = delete;
  Table(Table &&) = delete;

  explicit Table(int n) {
    n_ = n;
    table_ = new int *[n];
    for (int i = 0; i < n; ++i) {
      table_[i] = new int[n];
      std::memset(table_[i], 0, n * sizeof(int));
    }
  }

  Table(const Table &table) {
    n_ = table.n_;
    table_ = new int *[n_];
    for (int i = 0; i < n_; ++i) {
      table_[i] = new int[n_];
      for (int j = 0; j < n_; ++j) {
        table_[i][j] = table.table_[i][j];
      }
    }
  }

  void ClearTable() {
    for (int i = 0; i < n_; ++i) {
      std::memset(table_[i], 0, n_ * sizeof(int));
    }
  }

  void ClearTableOnPoint() {
    for (int i = 0; i < n_; ++i) {
      std::memset(table_[i], 0, n_ * sizeof(int));
    }
  }

  void PointCells(int i, int j, int value) {
    for (int k = i + 1; k < n_; ++k) {
      table_[k][j] += value;
    }

    for (int k = i - 1; k >= 0; --k) {
      table_[k][j] += value;
    }

    for (int m = j + 1; m < n_; ++m) {
      table_[i][m] += value;
    }

    for (int m = j + 1, k = i + 1; m < n_ && k < n_; ++m, ++k) {
      table_[k][m] += value;
    }

    for (int m = j + 1, k = i - 1; m < n_ && k >= 0; ++m, --k) {
      table_[k][m] += value;
    }
  }

  void ShowTable() {
    for (int i = 0; i < n_; ++i) {
      for (int j = 0; j < n_; ++j) {
        std::cout << table_[i][j] << ' ';
      }
      std::cout << '\n';
    }
  }

  ~Table() {
    for (int i = 0; i < n_; ++i) {
      delete[] table_[i];
    }
    delete[] table_;
  }
};

int Solution();

int FindResult(Table &my_table, int row, int &result);

int main() {
  Solution();

  return 0;
}

int Solution() {
  int n = 0;
  std::cin >> n;

  Table table(n);
  int result = 0;

  FindResult(table, 0, result);

  std::cout << result << '\n';

  return 0;
}

int FindResult(Table &my_table, int row, int &result) {
  bool queen_set = false;

  int **table = my_table.GetTable();
  int n = my_table.GetN();

  if (row > n) {
    return 0;
  }

  for (int i = 0; i < n; ++i) {
    if (table[i][row] == 0) {
      table[i][row] += 1;
      my_table.PointCells(i, row, 1);
      queen_set = true;
    }
    if (queen_set) {
      if (row == n - 1) {
        ++result;
        my_table.PointCells(i, row, -1);
        --(table[i][row]);
        return 0;
      }
      FindResult(my_table, row + 1, result);

      queen_set = false;
      my_table.PointCells(i, row, -1);
      --(table[i][row]);
    }
  }

  return 0;
}