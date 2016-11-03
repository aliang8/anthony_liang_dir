#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int is_directory(const char *f){
  struct stat file_stat;
  stat(f,&file_stat);
  return S_ISDIR(file_stat.st_mode);
}

int get_file_size(const char *f){
  struct stat file_stat;
  stat(f,&file_stat);
  int size = file_stat.st_size;
  return size;
}

int main (int c, char *v[]) {
  int dirSize = 0;
  struct dirent *pDirent;
  DIR *pDir;
  
  printf("Statistics for Directory : %s \n", v[1]);

  if (c < 2) {
    printf ("Usage: ./a.out <dirname>\n");
    return 1;
  }
  pDir = opendir (v[1]);
  if (pDir == NULL) {
    printf ("Cannot open directory '%s'\n", v[1]);
    return 1;
  }

  printf("Directories: \n");
  while ((pDirent = readdir(pDir)) != NULL){
    char *file = pDirent->d_name;
    if(is_directory(file))
      printf("%s\n",file);
  }
  rewinddir(pDir);
  printf("Regular files: \n");
  while ((pDirent = readdir(pDir)) != NULL){
    char *file = pDirent->d_name;
    if(!(is_directory(file))){
      dirSize += get_file_size(file);
      printf("%s\n",file);
    }
  }
  printf("Total Directory Size: %i\n", dirSize);
  closedir (pDir);
  return 0;
}
