//mod fsize to print other info in inode entry
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

void print_permissions(mode_t mode) {
  char permissions[10] = "----------";

  if (S_ISDIR(mode)) permissions[0] = 'd';
  else if (S_ISLNK(mode)) permissions[0] = 'l';
  else if (S_ISREG(mode)) permissions[0] = '-';

  //user perms
  if (mode & S_IRUSR) permissions[1] = 'r';
  if (mode & S_IWUSR) permissions[2] = 'w';
  if (mode & S_IXUSR) permissions[3] = 'x';

  //grp perms
  if (mode & S_IRGRP) permissions[4] = 'r';
  if (mode & S_IWGRP) permissions[5] = 'w';
  if (mode & S_IXGRP) permissions[6] = 'x';

  //other perms
  if (mode & S_IROTH) permissions[7] = 'r';
  if (mode & S_IWOTH) permissions[8] = 'w';
  if (mode & S_IWOTH) permissions[9] = 'x';

  printf("Permissions: %s\n", permissions);
}

int main(int argc, char *argv[]) {
  struct stat st;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    return 1;
  }

  if (stat(argv[1], &st) == -1) {
    perror("stat");
    return 1;
  }

  printf("File: %s\n", argv[1]);
  printf("Size: %ld bytes\n", st.st_size);
  printf("Inode: %ld\n", st.st_ino);
  printf("Permissions: ");
  print_permissions(st.st_mode);
  printf("Number of links: %ld\n", st.st_nlink);
  printf("Owner: UID=%ld Group: GID=%ld\n", (long)st.st_uid, (long)st.st_gid);

  printf("Last access:  %s", ctime(&st.st_atime));
  printf("Last modification: %s", ctime(&st.st_mtime));
  printf("Last status change: %s", ctime(&st.st_ctime));

  return 0;
}
