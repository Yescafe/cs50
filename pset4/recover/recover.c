#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
BYTE buffer[512];
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
  if (argc != 2) {
    printf("Usage: ./recover IMAGE\n");
    return 1;
  }

  FILE* raw_file = fopen(argv[1], "r");
  char filename[] = "000.jpg";
  FILE* output = NULL;
  int counter = 0;

  while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE) {
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff
        && (buffer[3] | 0x0f) == 0xef) {
      if (output != NULL) {
        fclose(output);
        sprintf(filename, "%.3i", ++counter);
        filename[3] = '.';
      }
      output = fopen(filename, "w+");
    }
    if (output != NULL) fwrite(buffer, 1, BLOCK_SIZE, output);
  }
  if (output != NULL) fclose(output);

  return 0;
}

