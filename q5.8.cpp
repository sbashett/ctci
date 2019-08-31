#include <iostream>

using namespace std;

typedef unsigned char BYTE;

void draw_intermediate_bytes(BYTE *screen, int start_byte_index,
                             int end_byte_index) {
  for (int it = start_byte_index + 1; it < end_byte_index; it++) {
    screen[it] = 0xFF;
  }
}

void draw_start_offset(BYTE *screen, int start_byte_index,
                       int start_byte_offset) {
  BYTE mask = 1;
  mask = mask << (8 - start_byte_offset - 1);
  mask = mask - 1;
  screen[start_byte_index] |= mask;
}

void draw_end_offset(BYTE *screen, int end_byte_index, int end_byte_offset) {
  BYTE mask = 1;
  mask = mask << (8 - end_byte_offset) - 1;
  mask = ~(mask - 1);
  screen[end_byte_index] |= mask;
}

void drawLine(BYTE *screen, int width, int x1, int x2, int y) {

  // int screen_len = *(&screen + 1) - screen;
  // int h = screen_len / width;
  int start_byte_index = ((y * width) + (x1 / 8));
  int start_byte_offset = x1 % 8;
  int end_byte_index = ((y * width) + (x2 / 8));
  int end_byte_offset = x2 % 8;

  if (end_byte_index != start_byte_index)
    draw_intermediate_bytes(screen, start_byte_index, end_byte_index);

  draw_start_offset(screen, start_byte_index, start_byte_offset);
  draw_end_offset(screen, end_byte_index, end_byte_offset);

  for (size_t it = 0; it < 64 * 64; it++)
    cout << (int)screen[it] << ',';

  return;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {

  BYTE screen[64 * 64] = {0};
  int width = 64;

  drawLine(screen, width, 10, 280, 25);

  return 0;
}