#include <iostream>
#include <string>
#include <vector>

using namespace std;

void simple_rotate_image(int *image, int *return_image, int N) {

  for (int rows = 0; rows < N; rows++) {
    for (int cols = 0; cols < N; cols++) {
      *(return_image + (cols * N) + (N - rows - 1)) =
          *(image + (rows * N) + cols);
    }
  }
}

void inplace_rotate_image(int *image, int N) {
  // anticlockwise rotation. just invert the steps in inner loop for clockwise
  int temp_store = 0;
  for (int ref_counter = 0; ref_counter < N / 2; ref_counter++) {
    for (int it = ref_counter; it < N - ref_counter - 1; it++) {
      temp_store = *(image + ref_counter * N + it);
      *(image + ref_counter * N + it) = *(image + it * N + N - 1 - ref_counter);
      *(image + it * N + N - 1 - ref_counter) =
          *(image + (N - 1 - ref_counter) * N + (N - it - 1));
      *(image + (N - 1 - ref_counter) * N + (N - it - 1)) =
          *(image + (N - it - 1) * N + ref_counter);
      *(image + (N - it - 1) * N + ref_counter) = temp_store;
    }
  }
}

void print_matrix(int *matrix, int N) {
  for (int rows = 0; rows < N; rows++) {
    for (int cols = 0; cols < N; cols++) {
      cout << *(matrix + rows * N + cols) << " ";
    }

    cout << "\n";
  }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  int N = 5;
  // int image[N][N] = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15, 16}};
  int image[N][N] = {{1, 2, 3, 4, 5},
                     {6, 7, 8, 9, 10},
                     {11, 12, 13, 14, 15},
                     {16, 17, 18, 19, 20},
                     {21, 22, 23, 24, 25}};
  // int return_image[N][N] = {0}; //for testing simple rotate

  // simple_rotate_image(&image[0][0], &return_image[0][0], N);  //for testing
  // simple rotate

  cout << "original matrix: \n";
  print_matrix(&image[0][0], N);

  inplace_rotate_image(&image[0][0], N); // for testing inplace rotate

  cout << "rotated image: \n";
  // print_matrix(&return_image[0][0], N);  //for testing simple rotate
  print_matrix(&image[0][0], N); // for testing inplace rotate
}
