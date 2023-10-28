#include <iostream>
#include <cstring>

/*
1) Комментарии удалены
2) Члены класса используются явно при решении. Метод FindResult идейно не является членом класса.
   Можно написать функцию которая явно бы возвращала указатель на массив, и _n_, но это мало бы отличалось от нынешнего
явного использования элементов класса. Поэтому не вижу смысла выносить их в секцию private 3) Использую правило трех,
так как правило пяти избыточно в данной задаче.
*/

class Table {
 public:
  int **_table_;
  int _n_;

  explicit Table(int n) {
    _n_ = n;
    _table_ = new int *[n];
    for (int i = 0; i < n; ++i) {
      _table_[i] = new int[n];
      std::memset(_table_[i], 0, n * sizeof(int));
    }
  }

  Table(const Table &table) {
    _n_ = table._n_;
    _table_ = new int *[_n_];
    for (int i = 0; i < _n_; ++i) {
      _table_[i] = new int[_n_];
      for (int j = 0; j < _n_; ++j) {
        _table_[i][j] = table._table_[i][j];
      }
    }
  }

  void ClearTable() {
    for (int i = 0; i < _n_; ++i) {
      std::memset(_table_[i], 0, _n_ * sizeof(int));
    }
  }

  void ClearTableOnPoint() {
    for (int i = 0; i < _n_; ++i) {
      std::memset(_table_[i], 0, _n_ * sizeof(int));
    }
  }

  void PointCells(int i, int j, int value) {
    for (int k = i + 1; k < _n_; ++k) {
      _table_[k][j] += value;
    }

    for (int k = i - 1; k >= 0; --k) {
      _table_[k][j] += value;
    }

    for (int m = j + 1; m < _n_; ++m) {
      _table_[i][m] += value;
    }

    for (int m = j + 1, k = i + 1; m < _n_ && k < _n_; ++m, ++k) {
      _table_[k][m] += value;
    }

    for (int m = j + 1, k = i - 1; m < _n_ && k >= 0; ++m, --k) {
      _table_[k][m] += value;
    }
  }

  void ShowTable() {
    for (int i = 0; i < _n_; ++i) {
      for (int j = 0; j < _n_; ++j) {
        std::cout << _table_[i][j] << ' ';
      }
      std::cout << '\n';
    }
  }

  ~Table() {
    for (int i = 0; i < _n_; ++i) {
      delete[] _table_[i];
    }
    delete[] _table_;
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

  std::cout << result << '\n';

  return 0;
}

int FindResult(Table &table, int row, int &result) {
  bool queen_set = false;

  if (row > table._n_) {
    return 0;
  }

  for (int i = 0; i < table._n_; ++i) {
    if (table._table_[i][row] == 0) {
      table._table_[i][row] += 1;
      table.PointCells(i, row, 1);
      queen_set = true;
    }
    if (queen_set) {
      if (row == table._n_ - 1) {
        ++result;
        table.PointCells(i, row, -1);
        --(table._table_[i][row]);
        return 0;
      }
      FindResult(table, row + 1, result);

      queen_set = false;
      table.PointCells(i, row, -1);
      --(table._table_[i][row]);
    }
  }

  return 0;
}