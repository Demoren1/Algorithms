#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>
#include <iostream>
#include <initializer_list>

class MatrixIsDegenerateError : public std::runtime_error {
 public:
  MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {
  }
};

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

template <typename T, size_t Rows, size_t Cols>
class Matrix {
 private:
 public:
  T matrix_[Rows][Cols];

  void ShowMatrix() const {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Cols; ++j) {
        std::cout << matrix_[i][j] << ' ';
      }
      std::cout << '\n';
    }
  }

  size_t RowsNumber() const {
    return Rows;
  }

  size_t ColumnsNumber() const {
    return Cols;
  }

  T& operator()(const size_t row_num, const size_t col_num) {
    return matrix_[row_num][col_num];
  }

  const T& operator()(const size_t row_num, const size_t col_num) const {
    return matrix_[row_num][col_num];
  }

  T& At(const size_t row_num, const size_t col_num) {
    if (row_num >= Rows || col_num >= Cols) {
      throw MatrixOutOfRange{};
    }

    return matrix_[row_num][col_num];
  }

  const T& At(const size_t row_num, const size_t col_num) const {
    if (row_num >= Rows || col_num >= Cols) {
      throw MatrixOutOfRange{};
    }

    return matrix_[row_num][col_num];
  }

  Matrix& operator+=(const Matrix& other) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Cols; ++j) {
        matrix_[i][j] += other(i, j);
      }
    }

    return *this;
  }

  Matrix& operator-=(const Matrix& other) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Cols; ++j) {
        matrix_[i][j] -= other(i, j);
      }
    }

    return *this;
  }

  Matrix& operator*=(const Matrix<T, Cols, Cols>& other) {
    Matrix res_matrix;
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Cols; ++j) {
        res_matrix(i, j) = 0;
        for (size_t index = 0; index < Cols; ++index) {
          res_matrix(i, j) += matrix_[i][index] * other(index, j);
        }
      }
    }
    *this = res_matrix;

    return *this;
  }

  friend Matrix operator+(const Matrix& first, const Matrix& second) {
    Matrix result = first;
    result += second;
    return result;
  }

  friend Matrix operator-(const Matrix& first, const Matrix& second) {
    Matrix result = first;
    result -= second;
    return result;
  }

  bool operator==(const Matrix& other) const {
    bool eq_flag = true;

    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Cols; ++j) {
        if (matrix_[i][j] != other(i, j)) {
          eq_flag = false;
        }
      }
    }

    return eq_flag;
  }

  bool operator!=(const Matrix& other) const {
    return !(*this == other);
  }

  friend std::ostream& operator<<(std::ostream& os, const Matrix& tmp_matrix) {
    for (size_t i = 0; i < Rows; i++) {
      for (size_t j = 0; j < Cols; j++) {
        if (j > 0) {
          os << ' ';
        }
        os << tmp_matrix(i, j);
      }
      os << '\n';
    }
    return os;
  }

  friend std::istream& operator>>(std::istream& is, Matrix& tmp_matrix) {
    for (size_t i = 0; i < Rows; i++) {
      for (size_t j = 0; j < Cols; j++) {
        is >> tmp_matrix(i, j);
      }
    }
    return is;
  }
};

template <typename T, size_t Rows, size_t Cols, typename U>
Matrix<T, Rows, Cols>& operator*=(Matrix<T, Rows, Cols>& matrix, const U& number) {
  auto new_number = static_cast<T>(number);
  for (size_t i = 0; i < Rows; i++) {
    for (size_t j = 0; j < Cols; j++) {
      matrix.matrix_[i][j] *= new_number;
    }
  }
  return matrix;
}
template <typename T, size_t Rows, size_t Cols, typename U>
Matrix<T, Rows, Cols> operator*(const Matrix<T, Rows, Cols>& matrix, const U& number) {
  Matrix<T, Rows, Cols> result = matrix;
  result *= number;
  return result;
}
template <typename T, size_t Rows, size_t Cols, typename U>
Matrix<T, Rows, Cols> operator*(const U& number, const Matrix<T, Rows, Cols>& matrix) {
  return matrix * number;
}
template <typename T, size_t Rows, size_t Cols, size_t OtherCols>
Matrix<T, Rows, OtherCols> operator*(const Matrix<T, Rows, Cols>& first, const Matrix<T, Cols, OtherCols>& second) {
  Matrix<T, Rows, OtherCols> result;
  for (size_t n = 0; n < Rows; n++) {
    for (size_t k = 0; k < OtherCols; k++) {
      result.matrix_[n][k] = 0;
      for (size_t m = 0; m < Cols; m++) {
        result.matrix_[n][k] += first.matrix_[n][m] * second.matrix_[m][k];
      }
    }
  }
  return result;
}

template <typename T, size_t Rows, size_t Cols, typename U>
Matrix<T, Rows, Cols>& operator/=(Matrix<T, Rows, Cols>& tmp_matrix, const U& num) {
  for (size_t i = 0; i < Rows; i++) {
    for (size_t j = 0; j < Cols; j++) {
      tmp_matrix(i, j) /= num;
    }
  }
  return tmp_matrix;
}

template <typename T, size_t Rows, size_t Cols, typename U>
Matrix<T, Rows, Cols> operator/(const Matrix<T, Rows, Cols>& tmp_matrix, const U& number) {
  Matrix<T, Rows, Cols> result = tmp_matrix;
  result /= number;
  return result;
}

template <typename T, size_t Rows, size_t Cols>
Matrix<T, Cols, Rows> GetTransposed(const Matrix<T, Rows, Cols>& to_trans_matrix) {
  Matrix<T, Cols, Rows> res_matrix;

  for (size_t i = 0; i < Cols; i++) {
    for (size_t j = 0; j < Rows; j++) {
      res_matrix(i, j) = to_trans_matrix(j, i);
    }
  }
  return res_matrix;
}

#endif