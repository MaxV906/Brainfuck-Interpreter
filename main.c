#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

void interpreter(char *content) {

  uint8_t *blocks = malloc(sizeof(uint8_t) * 255);
  uint8_t current_block = 0;

  int loop_start;

  for (int i = 0; i < 255; i++) {
    blocks[i] = 0;
  }

  for (int i = 0; i < strlen(content); i++) {
    
    if (content[i] == '[') loop_start = i;
    else if (content[i] == ']') {
      if (blocks[current_block] != 0) {
        i = loop_start;
      }
    }
    else if (content[i] == '>') current_block++;
    else if (content[i] == '<') current_block--;
    else if (content[i] == '+') blocks[current_block]++;
    else if (content[i] == '-') blocks[current_block]--;
    else if (content[i] == '.') printf("%c", blocks[current_block]);
    else {
      if (content[i] != '\n' && content[i] != ' ') {
	fprintf(stderr, "Syntax Error: Unknown operator %d: '%c'\n", i, content[i]);
	break;
      }
    }

    sleep(0.5);

  }

  printf("\n");

  free(blocks);

}


int main (int argc, char** argv) {

  if (argc < 2) {
    fprintf(stderr, "Too little arguments.\n");
    return 1;
  }

  char *file = argv[1];

  long file_size;
  char *content;
  
  FILE *f = fopen(file, "rb");

  if (!f) {
    fprintf(stderr, "Can't open the file.\n");
    return 1;
  }

  fseek(f, 0, SEEK_END);
  file_size = ftell(f);
  fseek(f, 0, SEEK_SET);

  content = (char *)malloc(file_size + 1);
  
  fread(content, 1, file_size, f);


  interpreter(content);

  free(content);
  fclose(f);
  return 0;

}
