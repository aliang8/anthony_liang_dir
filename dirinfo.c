#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>

void check_error() {
  if (errno) {
    printf("Error #%d, %s\n", errno, strerror(errno));
  }
}

int print_dirinfo(DIR* current_dir, unsigned char file_type) {
  struct dirent* dir_info;
  struct stat data;
  int sum = 0;
  while ((dir_info = readdir(current_dir)) != NULL) {
    if (dir_info->d_type == file_type) {
      printf("%s\n", dir_info->d_name);
      if (dir_info->d_type == DT_REG) {
	stat(dir_info->d_name, &data);
	sum += data.st_size;
      }
    }
  }
  return sum;
}

int main(int c, char *v[]) {
  DIR *d;
  printf("Statistics for Directory : %s \n", v[1]);
  if (c < 2) {
    printf ("Usage: ./a.out <dirname>\n");
    return 1;
  }

  d = opendir (v[1]);
  check_error();

  if (d == NULL) {
    printf ("Cannot open directory '%s'\n", v[1]);
    return 1;
  }

  printf("Directory files:\n");
  print_dirinfo(d, DT_DIR);

  rewinddir(d);

  printf("Regular files:\n");
  int size = print_dirinfo(d, DT_REG);
  printf("Total size of regular files: %d bytes\n", size);
  closedir(d);
  return 0;
}
