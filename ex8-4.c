#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int fseek(FILE *fp, long offset, int origin);

int fseek(FILE *fp, long offset, int origin) {
  if (fp && origin != SEEK_END) {
    if (fflush(fp) == EOF) {
      return -1;
    }
  }

  int fd = fileno(fp);
  if (fd == -1) {
    errno = EBADF;
    return -1;
  }

  off_t new_pos = 0; 
  switch (origin) {
    case SEEK_SET:
      new_pos = offset;
      break;
    case SEEK_CUR:
      new_pos = lseek(fd, 0, SEEK_CUR) + offset;
      break;
    case SEEK_END:
      new_pos = lseek(fd, 0, SEEK_END) + offset;
      break;
    default:
      errno = EINVAL;
      return -1;
  }

  if (lseek(fd, new_pos, SEEK_SET) == -1) {
    return -1;
  }

  return 0;
}

int main() {
    // Open a file for writing (create it if it doesn't exist)
    FILE *fp = fopen("testfile.txt", "w+");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Write some data to the file
    fprintf(fp, "Hello, world! This is a test file.\n");

    // Perform a seek to the beginning
    if (fseek(fp, 0, SEEK_SET) != 0) {
        perror("Error seeking to beginning");
        fclose(fp);
        return 1;
    }

    // Read the first few characters
    char buffer[20];
    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("Data read after SEEK_SET: %s", buffer);
    } else {
        perror("Error reading file");
        fclose(fp);
        return 1;
    }

    // Seek to 6 bytes from the beginning of the file
    if (fseek(fp, 6, SEEK_SET) != 0) {
        perror("Error seeking to offset 6");
        fclose(fp);
        return 1;
    }

    // Read the next part of the file
    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("Data read after SEEK_SET 6: %s", buffer);
    } else {
        perror("Error reading file");
        fclose(fp);
        return 1;
    }

    // Seek to 5 bytes from the current position (i.e., from the 6th byte)
    if (fseek(fp, 5, SEEK_CUR) != 0) {
        perror("Error seeking to offset 5 from current position");
        fclose(fp);
        return 1;
    }

    // Read more data after seeking from the current position
    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("Data read after SEEK_CUR: %s", buffer);
    } else {
        perror("Error reading file");
        fclose(fp);
        return 1;
    }

    // Seek to 5 bytes from the end of the file
    if (fseek(fp, -5, SEEK_END) != 0) {
        perror("Error seeking to offset -5 from end");
        fclose(fp);
        return 1;
    }

    // Read the last part of the file
    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("Data read after SEEK_END: %s", buffer);
    } else {
        perror("Error reading file");
        fclose(fp);
        return 1;
    }

    // Close the file
    fclose(fp);

    return 0;
}
