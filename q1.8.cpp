#include "common_header.hpp"
#include <iostream>
#include <list>
#include <vector>

using namespace std;

void replace_row_with_zeros(int *matrix, int row, int N) {
  for (int cols = 0; cols < N; cols++)
    *(matrix + row * N + cols) = 0;
}

void replace_col_with_zeros(int *matrix, int col, int M, int N) {
  for (int rows = 0; rows < M; rows++)
    *(matrix + rows * N + col) = 0;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  int M = 3, N = 5;
  int matrix[M][N] = {{1, 0, 3, 4, 5}, {6, 7, 8, 0, 10}, {11, 12, 13, 14, 15}};
  cout << "original matrix \n";
  myspace::print_matrix(&matrix[0][0], M, N);
  int it;

  list<int> list_rows, list_cols;
  vector<int> vector_rows_zero, vector_cols_zero, vector_rem_rows,
      vector_rem_cols;

  for (it = 0; it < M; it++)
    list_rows.push_back(it);
  for (it = 0; it < N; it++)
    list_cols.push_back(it);

START_LOOP:
  if (vector_rows_zero.size() > 0)
    for (int rows : vector_rows_zero)
      replace_row_with_zeros(&matrix[0][0], rows, N);
  if (vector_cols_zero.size() > 0)
    for (int cols : vector_cols_zero)
      replace_col_with_zeros(&matrix[0][0], cols, M, N);
  for (int rows : vector_rem_rows)
    list_rows.remove(rows);
  for (int cols : vector_rem_cols)
    list_cols.remove(cols);

  vector_rows_zero.clear();
  vector_cols_zero.clear();
  vector_rem_rows.clear();
  vector_rem_cols.clear();

  for (int rows : list_rows) {
    for (int cols : list_cols) {
      if (matrix[rows][cols] == 0) {
        vector_rows_zero.push_back(rows);
        vector_cols_zero.push_back(cols);
        vector_rem_rows.push_back(rows);
        vector_rem_cols.push_back(cols);
        goto START_LOOP;
      }
    }
    vector_rem_rows.push_back(rows);
  }

  cout << "modified matrix \n";
  myspace::print_matrix(&matrix[0][0], M, N);
  return 0;
}
