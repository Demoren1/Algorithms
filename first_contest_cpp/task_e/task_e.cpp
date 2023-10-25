#include <iostream>
#include <cstring>

class Table {
 public:
  int **_table;
  int _n;

  explicit Table(int n) {
    _n = n;
    _table = new int *[n];
    for (int i = 0; i < n; ++i) {
      _table[i] = new int[n];
      std::memset(_table[i], 0, n * sizeof(int));
    }
  }

  void ClearTable() {
    for (int i = 0; i < _n; ++i) {
      std::memset(_table[i], 0, _n * sizeof(int));
    }
  }

  void ClearTableOnPoint() {
    for (int i = 0; i < _n; ++i) {
      std::memset(_table[i], 0, _n * sizeof(int));
    }
  }

  void PointCells(int i, int j, int value) {
    for (int k = i + 1; k < _n; ++k) {
      _table[k][j] += value;
    }

    for (int k = i - 1; k >= 0; --k) {
      _table[k][j] += value;
    }

    for (int m = j + 1; m < _n; ++m) {
      _table[i][m] += value;
    }

    for (int m = j + 1, k = i + 1; m < _n && k < _n; ++m, ++k) {
      _table[k][m] += value;
    }

    for (int m = j + 1, k = i - 1; m < _n && k >= 0; ++m, --k) {
      _table[k][m] += value;
    }
  }

  void ShowTable() {
    for (int i = 0; i < _n; ++i) {
      for (int j = 0; j < _n; ++j) {
        std::cout << _table[i][j] << ' ';
      }
      std::cout << '\n';
    }
  }

  ~Table() {
    for (int i = 0; i < _n; ++i) {
      delete[] _table[i];
    }
    delete[] _table;
  }
};

int Solution();

int FindResult(Table &table, int row, int &result);

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

  // table.PointCells(2, 1, 1);
  // table.ShowTable();
  // table.PointCells(0, 1, -1);
  // table.ShowTable();

  // std::cout << "result = " << result << '\n';
  std::cout << result << '\n';

  return 0;
}

int FindResult(Table &table, int row, int &result) {
  bool queen_set = false;

  if (row > table._n) {
    return 0;
  }

  for (int i = 0; i < table._n; ++i) {
    if (row == 0) {
      // std::` << "New row " << i << '\n';
    }

    // std::cout << '\n';
    // table.ShowTable();
    // std::cout << '\n';

    if (table._table[i][row] == 0) {
      table._table[i][row] += 1;
      table.PointCells(i, row, 1);
      queen_set = true;
    }
    if (queen_set) {
      if (row == table._n - 1) {
        ++result;
        // std::cout << "GET ONE\n";
        table.PointCells(i, row, -1);
        --(table._table[i][row]);
        return 0;
      }
      FindResult(table, row + 1, result);

      queen_set = false;
      table.PointCells(i, row, -1);
      --(table._table[i][row]);
    }
  }

  return 0;
}