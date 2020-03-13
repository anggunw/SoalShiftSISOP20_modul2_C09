#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>

int main() {
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1) {
    char folder_name[80] = "/home/gun/";
    char temp[30];
    time_t rawtime;
    struct tm *info;
    int status;

    pid_t child_a, child_a2, child_b;
    
    child_a = fork();
    
    // NO 2A - MEMBUAT FOLDER SETIAP 30 DETIK
    if(child_a == 0){
      time (&rawtime);
      info = localtime(&rawtime);
      strftime(temp, 30, "%Y-%m-%d_%X", info);
      strcat(folder_name, temp);

      child_a2 = fork();
      // membuat folder
      if(child_a2 == 0){
        char *argv[] = {"mkdir", folder_name, NULL};
        execv("/bin/mkdir", argv);
      }
      
      while ((wait(&status)) > 0);
      // NO 2B - DOWNLOAD 20 GAMBAR SETIAP 5 DETIK
      for(int i=0;i<20;i++){
        child_b = fork();

        if(child_b == 0){
          // get epoch unix
          time_t seconds;
          seconds = time(NULL);

          // get image size
          int size = (seconds%1000)+100;

          // get current time
          char file_name[30];
          time (&rawtime);
          info = localtime(&rawtime);
          strftime(file_name, 30, "%Y-%m-%d_%X", info); 

          // url to download
          char url[] = "https://picsum.photos/";
          char file_size[30];
          sprintf(file_size, "%d", size);
          strcat(url, file_size); // url nya

          // lokasi download
          char file_path[50];
          strcpy(file_path, folder_name);
          strcat(file_path, "/"); //home/user/....
          strcat(file_path, file_name);

          // download using wget
          char *argv[] = {"wget", url, "-O", file_path, NULL};
          execv("/usr/bin/wget", argv);
        }
        sleep(5);
      }
      waitpid(child_b, &status, 0);
      // NO 2C - ZIP FOLDER
      char zip_name[50];
      strcpy(zip_name, temp);
      strcat(zip_name, "/");
      char *argv[] = {"zip", temp, "-r", "-m", zip_name, NULL};
      execv("/usr/bin/zip", argv);
    }
    sleep(30);
  }
}