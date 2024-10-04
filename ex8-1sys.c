//implement cat using syscalls (read write open close)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
  int fd;
  ssize_t nread;
  char buffer[BUFFER_SIZE];

  if (argc == 1) {
    while ((nread = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
      write(STDOUT_FILENO, buffer, nread);
    }
    if (nread == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
  } else {
      for (int i = 1; i < argc; i++) {
           fd = open(argv[i], O_RDONLY);
           if (fd == -1) {
              perror("open");
              exit(EXIT_FAILURE);
           }
           while ((nread = read(fd, buffer, sizeof(buffer))) > 0) {
              write(STDOUT_FILENO, buffer, nread);
           }
           if (nread == -1) {
             perror("read");
             exit(EXIT_FAILURE);
           }
           close(fd);
          }
        }
      return 0;
}
