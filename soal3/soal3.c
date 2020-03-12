#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>

int main() {
  pid_t child, child1, child2, child3, child4, child5, child6;
  int status;
 
  child = fork();

  // CHILD - NO 3A CREATE FOLDER INDOMIE
  if (child == 0) {
    printf("membuat folder indomie\n");
    char *argv[] = {"mkdir", "-p", "/home/gun/modul2/indomie", NULL};
    execv("/bin/mkdir", argv);
  }
  child1 = fork(); 
  // CHILD1 - NO 3A CREATE FOLDER SEDAAP
  if (child1 == 0){
    sleep(5);
    printf("membuat folder sedaap\n");
    char *argv[] = {"mkdir", "-p", "/home/gun/modul2/sedaap", NULL};
    execv("/bin/mkdir", argv);
  }
  child2 = fork();
  // CHILD2 - NO 3B UNZIP
  if (child2 == 0) {
    printf("unzip jpg\n");
    char *argv[] = {"unzip", "/home/gun/Downloads/jpg.zip", "-d", "/home/gun/modul2/", NULL};
    execv("/usr/bin/unzip", argv);
  }
  waitpid(child, &status, 0);
  waitpid(child1, &status, 0);
  waitpid(child2, &status, 0);
  child3 = fork();
  // CHILD3 - NO 3C DAN 3D
  if(child3 == 0){
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("/home/gun/modul2/jpg/")) != NULL){
      while((ent = readdir (dir)) != NULL){
        char folder_name[] = "/home/gun/modul2/jpg/";
        strcat(folder_name, ent->d_name);
        // SKIP UNTUK . DAN ..
        if(strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0){
          continue;
        }
        // NO 3C - JIKA FOLDER, PINDAHKAN KE FOLDER INDOMIE
        else if(ent->d_type == DT_DIR){
          child4 = fork();
          // NO 3C - MEMINDAHKAN FOLDER KE FOLDER INDOMIE
          if(child4 == 0){
            char *argv[] = {"mv", folder_name, "/home/gun/modul2/indomie/", NULL};
            execv("/bin/mv", argv);
          }
          waitpid(child4, &status, 0);
          printf("folder %s sudah dipindahkan\n", folder_name);
          char folder_name2 [] = "/home/gun/modul2/indomie/";
          strcat(folder_name2, ent->d_name);
          child5 = fork();
          // NO 3D - MEMBUAT FILE COBA1.TXT 
          if(child5 == 0){
            char file_name [] = "a";
            strcpy(file_name, folder_name2);
            strcat(file_name, "/coba1.txt");
            printf("membuat %s\n", file_name);
            char *argv[] = {"touch", file_name, NULL};
            execv("/usr/bin/touch", argv);
          }
          waitpid(child5, &status, 0);
          child6 = fork();
          // NO 3D - MEMBUAT FILE COBA2.TXT SETELAH 3 DETIK
          if(child6 == 0){
            sleep(3);
            char file_name2 [] = "a";
            strcpy(file_name2, folder_name2);
            strcat(file_name2, "/coba2.txt");
            printf("membuat %s\n", file_name2);
            char *argv[] = {"touch", file_name2, NULL};
            execv("/usr/bin/touch", argv);
          } 
          waitpid(child6, &status, 0); 
        }
        // NO 3C - JIKA FILE, PINDAHKAN KE FOLDER SEDAAP
        else if(ent->d_type == DT_REG){
          child4 = fork();
          if(child4 == 0){
            char *argv[] = {"mv", folder_name, "/home/gun/modul2/sedaap/", NULL};
            execv("/bin/mv", argv);
          }
          printf("file %s sudah dipindahkan\n", folder_name);
        }
      }
      closedir(dir);
      printf("selesai");
      
    }
  }
  return 0;
}