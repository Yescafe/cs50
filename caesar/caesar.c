#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  if (argc != 2) {
    printf("Usage: ./caesar key\n");
    return 1;
  }
  size_t s = strlen(argv[1]);
  for (int i = 0; i < s; ++i) {
    if (!isdigit(argv[1][i])) {
      printf("Usage: ./caesar key\n");
      return 1;
    }
  }
  int k = atoi(argv[1]);

  string plaintext = get_string("plaintext:  ");
  size_t len = strlen(plaintext);

  printf("ciphertext: ");
  for (int i = 0; i < len; ++i) {
    if (islower(plaintext[i])) {
      putchar((plaintext[i] - 'a' + k) % 26 + 'a');
    }
    else if (isupper(plaintext[i])) {
      putchar((plaintext[i] - 'A' + k) % 26 + 'A');
    }
    else {
      putchar(plaintext[i]);
    }
  }
  putchar('\n');

  return 0;
}

