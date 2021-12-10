#include <ctype.h>    // isalpha
#include <cs50.h>     // get_string
#include <string.h>   // strlen
#include <stdio.h>    // printf
#include <math.h>     // round

int main(void)
{
  string line = get_string("Text: ");
  size_t len = strlen(line);

  int count_letter, count_word, count_sentence;
  count_letter = count_sentence = 0;
  count_word = 1;

  for (int i = 0; i < len; ++i) {
    if (isalpha(line[i])) {
      ++count_letter;
    }
    else if (line[i] == ' ') {
      ++count_word;
    }
    else if (line[i] == '.' || line[i] == '!' || line[i] == '?') {
      ++count_sentence;
    }
  }

  // printf("%i letters\n%i words\n%i sentences\n",
  //    count_letter, count_word, count_sentence);

  double index = 0.0588 * count_letter * 100 / count_word -
      0.296 * count_sentence * 100 / count_word  - 15.8;
  int index_i = (int) round(index);
  if (index_i < 1) {
    printf("Before Grade 1\n");
  }
  else if (index_i >= 16) {
    printf("Grade 16+\n");
  }
  else {
    printf("Grade %i\n", index_i);
  }

  return 0;
}

