//write the program tail, default is 10 lines
//support tail -n

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_N 10

//circular buffer

typedef struct LineNode {
  char *line;
  struct LineNode *next;
} LineNode;

typedef struct {
  LineNode *head;
  LineNode *tail;
  int size;
  int capacity;
} LineBuffer;

LineBuffer *create_buffer(int capacity) {
  LineBuffer *buffer = malloc(sizeof(LineBuffer));
  if (!buffer) {
      perror("malloc");
      exit(EXIT_FAILURE);
  }
  buffer->head = NULL;
  buffer->tail = NULL;
  buffer->size = 0;
  buffer->capacity = capacity;
  return buffer;
}

void add_line(LineBuffer *buffer, const char *line) {
  LineNode *new_node = malloc(sizeof(LineNode));
  if (!new_node) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  new_node->line = strdup(line);
  if (!new_node->line) {
    perror("strdup");
    exit(EXIT_FAILURE);
  }
  new_node->next = NULL;
  
  if (buffer->size == buffer->capacity) {
    LineNode *old_head = buffer->head;
    buffer->head = buffer->head->next;
    free(old_head->line);
    free(old_head);
  } else {
    buffer->size++;
  }

  if (buffer->tail) {
      buffer->tail->next = new_node;
  } else {
      buffer->head = new_node;
  }
  buffer->tail = new_node;
}

void print_buffer(const LineBuffer *buffer) {
  LineNode *current = buffer->head;
  while (current) {
    printf("%s", current->line);
    current = current->next;
  }
}

void free_buffer(LineBuffer *buffer) {
  LineNode *current = buffer->head;
  while (current) {
    LineNode *next = current->next;
    free(current->line);
    free(current);
    current = next;
  }
  free(buffer);
}

int main(int argc, char *argv[]) {
  int n = DEFAULT_N;
  if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'n') {
    if (argc > 2) {
      n = atoi(argv[2]);
      if (n <= 0) {
        fprintf(stderr, "error: invalid number of lines %d\n", n);
        return EXIT_FAILURE;
      }
    } else {
        fprintf(stderr, "error: missing number after -n\n");
        return EXIT_FAILURE;
      }
    }

    LineBuffer *buffer = create_buffer(n);
    char line[1024];

    while (fgets(line, sizeof(line), stdin)) {
      add_line(buffer, line);
    }

    print_buffer(buffer);
    free_buffer(buffer);

    return 0;
}

