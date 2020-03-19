# SoalShiftSISOP20_modul2_C09

* [Soal 1](#soal1)
      
* [Soal 2](#soal2)
      
* [Soal 3](#soal3)


## Soal 1 <a name="soal1"></a>
```
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main(int argc, char *argv[])
{
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  if (pid < 0)
  {
    exit(EXIT_FAILURE);
  }

  if (pid > 0)
  {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0)
  {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0)
  {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  int i = 0;
  while (i != 60)
  {
    int sleep, len, a, b, c, status;
    char inittime[30];
    printf("Script tes.c executed\n");
    char path[60], i[2],k[2],j[2];

    if(argc == 5)
    {
      printf("Argument yang dimasukkan valid\n");

      ///*
      a = atoi(argv[1]);
      b = atoi(argv[2]);
      c = atoi(argv[3]);
      strcpy(path, argv[4]);
      sprintf(inittime,"%02d:%02d:%02d\n", c, b, a);
      //printf("%s", inittime);

      time_t rawtime;
      struct tm *info;
      char buffer[30];
      time( &rawtime );
      info = localtime( &rawtime );

      strftime(buffer,30,"%X", info);
      //printf("%s\n", buffer );

      status = strcmp(inittime, buffer);

      if(status == 0)
      {
        char *argv[] = {"bash", path, NULL};
        execv("/bin/bash", argv);
      }
    }

    else
    {
      printf("Argument yang dimasukkan tidak valid\n");
      return 0;
    }


    i++;
    sleep(1);
  }

  return 0;
}
```

* ```if(argc == 5)``` 
  [Memeriksa Jumlah Argumen]
* ```time_t rawtime;
      struct tm *info;
      char buffer[30];
      time( &rawtime );
      info = localtime( &rawtime );```
  [Mendapatkan Waktu lokal]
* ```sprintf(inittime,"%02d:%02d:%02d\n", c, b, a);```
  [assign waktu ke string inittime dengan format diatas]
* ```status = strcmp(inittime, buffer);```
  [Membandingkan input yang dimasukkan sama dengan waktu sekarang atau tidak]
* ```if(status == 0)
      {
        char *argv[] = {"bash", path, NULL};
        execv("/bin/bash", argv);
      }```
   [Jika nilai status 0 maka bash script dijalankan]


## Soal 2 <a name="soal2"></a>
```
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

void genKillProgram(int pid, int code)
{
	FILE *fp;

	if(code == 0)
	{
		char sig[] = "SIGKILL";
	}

	else
	{
		char sig[] = "SIGSTOP";
	}

	char str[] = "
	"#include <stdio.h>"\n""
	"\n"
	"void main()\n"
	"{\n"
	"kill("pid" "," "code")"
	"}\n"
	;
	fp = fopen( "kill.c" , "w" );
	fwrite(str , 1 , sizeof(str)-1 , fp );
	fclose(fp);
	remove("kill.c");
}
int main(int argc, char *argv[])
{
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
    int code = 1;
  if(argv[1] == "-a")
  {
  	code = 1;
  	if (child_id == 0)
  	{
  		char *argv[]={"./kill",NULL};
  		execvp(argv[0],argv);
  	}
  	else
  	{
  		char *argv[] = {"cc", "-o", "./kill", "./kill.c", NULL};
  		execv("/usr/bin/cc", argv);
  	}
    genKillProgram(pid, code);
  }
  else if(argv[1] == "-b")
  {
  	code = 2;
  	if (child_id == 0)
  	{
  		// this is child
  		char *argv[]={"./kill",NULL};
     		 execvp(argv[0],argv);
  	}
  	else
  	{
  		// this is parent
    		  char *argv[] = {"cc", "-o", "./kill", "./kill.c", NULL};
      		execv("/usr/bin/cc", argv);
  	}
    genKillProgram(pid, code);
  }
  else
  {
  	exit(EXIT_FAILURE);
  }
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
```

* ```void genKillProgram(int pid, int code)```
  [Membuat kill program]
* ```if(argv[1] == "-a")```
  [Memeriksa Argumen]
* ```char *argv[]={"./kill",NULL};```
  execvp(argv[0],argv);
  [Child jalankan script c]
*  ```char *argv[] = {"cc", "-o", "./kill", "./kill.c", NULL};
   execv("/usr/bin/cc", argv);```
   [Parent men compile script c]
*  ```time (&rawtime);
   info = localtime(&rawtime);
   strftime(file_name, 30, "%Y-%m-%d_%X", info);```
   [Mendapatkan waktu lokal]	
*  ```char *argv[] = {"wget", url, "-O", file_path, NULL};
   execv("/usr/bin/wget", argv);```
   [Mendownload dari link char]
*  ```char zip_name[50];
   strcpy(zip_name, temp);
   strcat(zip_name, "/");
   char *argv[] = {"zip", temp, "-r", "-m", zip_name, NULL};
   execv("/usr/bin/zip", argv);```
   [Melakukan zip pada file]
	
	
## Soal 3 <a name="soal3"></a>
```
child = fork();
  // CHILD - NO 3A CREATE FOLDER INDOMIE
  if (child == 0) {
    printf("membuat folder indomie\n");
    char *argv[] = {"mkdir", "-p", "/home/gun/modul2/indomie", NULL};
    execv("/bin/mkdir", argv);
  }
```
* ```child = fork();``` membuat child process
* ```char *argv[] = {"mkdir", "-p", "/home/gun/modul2/indomie", NULL}; execv("/bin/mkdir", argv);``` menjalankan program mkdir di child process yaitu membuat directory indomie di /home/gun/modul2


```
child1 = fork(); 
  // CHILD1 - NO 3A CREATE FOLDER SEDAAP
  if (child1 == 0){
    sleep(5);
    printf("membuat folder sedaap\n");
    char *argv[] = {"mkdir", "-p", "/home/gun/modul2/sedaap", NULL};
    execv("/bin/mkdir", argv);
  }
```
* ```sleep(5)``` menunggu 5 detik sebelum membuat directory sedaap
* directory sedaap dibuat dengan exec mkdir


```
child2 = fork();
  // CHILD2 - NO 3B UNZIP
  if (child2 == 0) {
    printf("unzip jpg\n");
    char *argv[] = {"unzip", "/home/gun/Downloads/jpg.zip", "-d", "/home/gun/modul2/", NULL};
    execv("/usr/bin/unzip", argv);
  }
```
* ```char *argv[] = {"unzip", "/home/gun/Downloads/jpg.zip", "-d", "/home/gun/modul2/", NULL};``` unzip file jpg.zip yang terletak di /home/gun/Downloads/ ke /home/gun/modul2/
* ```execv("/usr/bin/unzip", argv);``` exec argv


```
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
```
* ```waitpid``` menunggu child process tertentu selesai
* ```if ((dir = opendir("/home/gun/modul2/jpg/")) != NULL)``` membuka directory /home/gun/modul2/jpg
* ``` while((ent = readdir (dir)) != NULL)``` cek semua isi directory
* ``` if(strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0){continue;}``` continue jika direktori . atau .. 
* ``` else if(ent->d_type == DT_DIR)``` mengecek apakah tipenya directory. Jika directory, maka directory tersebut dipindahkan ke directory indomie melalui process child 4 dengan menggunakan exec mv
* ```char *argv[] = {"mv", folder_name, "/home/gun/modul2/indomie/", NULL}; execv("/bin/mv", argv);``` memindahkan directory tersebut ke directory indomie
* ```char *argv[] = {"touch", file_name, NULL}; execv("/usr/bin/touch", argv);``` membuat file coba1.txt melalui process child5 dengan menggunakan exec
* ```char *argv[] = {"touch", file_name2, NULL}; execv("/usr/bin/touch", argv);``` membuat file coba2.txt melalui process child6 dengan menggunakan exec. Sebelum itu ada ```sleep(3)``` yang memberikan jeda 3 detik sebelum membuat file coba2.txt
* ```else if(ent->d_type == DT_REG)``` cek jika isi dari directory jpg merupakan file
* ```char *argv[] = {"mv", folder_name, "/home/gun/modul2/sedaap/", NULL}; execv("/bin/mv", argv);``` Memindahkan file tersebut ke directory sedaap menggunakan exec
* ```closedir(dir);``` menutup directory

Screenshot jawaban soal 3

Waktu pembuatan folder indomie

<p align="center">
  <img src="https://imgur.com/1BQrcaT.png" width="350" title="1">
</p>

Waktu pembuatan folder sedaap
<p align="center">
  <img src="https://imgur.com/fl39UBF" width="350" title="1">
</p>

Isi folder modul 2
<p align="center">
  <img src="https://imgur.com/qnNnH99.png" width="350" title="1">
</p>

Isi folder Indomie
<p align="center">
  <img src="https://imgur.com/M6iGCZk.png" width="350" title="1">
</p>

Isi folder 744.jpg
<p align="center">
  <img src="https://imgur.com/LTSe9xw.png" width="350" title="1">
</p>

Isi folder sedaap
<p align="center">
  <img src="https://imgur.com/S1tOLvi.png" width="350" title="1">
</p>
