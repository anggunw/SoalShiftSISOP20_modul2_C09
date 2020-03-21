# SoalShiftSISOP20_modul2_C09

* [Soal 1](#soal1)
      
* [Soal 2](#soal2)
      
* [Soal 3](#soal3)


## Soal 1 <a name="soal1"></a>
```

void execution(char path[])
{
  char *argv[] = {"bash", path, NULL};
  execv("/bin/bash", argv);
}

void failure()
{
  printf("Argument yang dimasukkan tidak valid\n");
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{

  pid_t pid, sid;
  pid = fork();

  if (pid < 0)
    exit(EXIT_FAILURE);

  if (pid > 0)
    exit(EXIT_SUCCESS);

  umask(0);
  sid = setsid();

  if (sid < 0)
    exit(EXIT_FAILURE);

  if ((chdir("/")) < 0)
    exit(EXIT_FAILURE);

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  if(argc != 5)
    failure();

  while (1)
  {
    int len, a, b, c, s1, s2, s3, b1, b2, b3, timing;
    char dettime[30], mentime[30], jamtime[30], i[2],k[2],j[2], path[30];

    a = atoi(argv[1]);
    b = atoi(argv[2]);
    c = atoi(argv[3]);
    strcpy(path, argv[4]);
    if(a > 59 || a < 0)
      failure();

    if(b > 59 || b < 0)
      failure();

    if(c > 23 || c < 0)
      failure();

    sprintf(dettime,"%02d\n", a);
    sprintf(mentime,"%02d\n", b);
    sprintf(jamtime,"%02d\n", c);
    time_t rawtime;
    struct tm *info;
    char buffdet[30], buffmen[30], buffjam[30];
    time( &rawtime );
    info = localtime( &rawtime );
    timing = 1;
    strftime(buffdet,30,"%S", info);
    strftime(buffmen,30,"%M", info);
    strftime(buffjam,30,"%H", info);
    s1 = strcmp(dettime, buffdet);
    s2 = strcmp(mentime, buffmen);
    s3 = strcmp(jamtime, buffjam);
    s1 = s1 + 50;
    s2 = s2 + 50;
    s3 = s3 + 50;
    b1 = strcmp(argv[1], "*");
    b2 = strcmp(argv[2], "*");
    b3 = strcmp(argv[3], "*");

    if(b1 == 0 && b2 == 0 && b3 == 0)
    {
      pid_t child_id;
      child_id = fork();

      if (child_id < 0)
      {
        exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
      }

      if (child_id == 0)
      {
        execution(path);
      }
    }

    else if( b1 == 0 && b2 == 0 && s3 == 0)
    {
      pid_t child_id;
      child_id = fork();

      if (child_id < 0)
      {
        exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
      }

      if (child_id == 0)
      {
        execution(path);
      }
    }

    else if( b1 == 0 && s2 == 0 && s3 == 0)
    {
      pid_t child_id;
      child_id = fork();

      if (child_id < 0)
      {
        exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
      }

      if (child_id == 0)
      {
        execution(path);
      }
    }

    else if( s1 == 0 && b2 == 0 && s3 == 0)
    {
      pid_t child_id;
      child_id = fork();

      if (child_id < 0)
      {
        exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
      }

      if (child_id == 0)
      {
        execution(path);
      }
    }

    else if( s1 == 0 && b2 == 0 && b3 == 0)
    {
      pid_t child_id;
      child_id = fork();

      if (child_id < 0)
      {
        exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
      }

      if (child_id == 0)
      {
        execution(path);
      }
    }

    else if(s1 == 0 && s2 == 0 && b3 == 0)
    {
      pid_t child_id;
      child_id = fork();

      if (child_id < 0)
      {
        exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
      }

      if (child_id == 0)
      {
        execution(path);
      }
    }

    else if(s1 == 0 && s2 == 0 && s3 == 0)
    {
      pid_t child_id;
      child_id = fork();

      if (child_id < 0)
      {
        exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
      }

      if (child_id == 0)
      {
        execution(path);
      }
    }
  }

  sleep(1);
  return 0;
}

```
Pada program diatas akan mengeksekusi file bash dengan jadwal yang telah ditetapkan. Pertama program akan memeriksa apakah jumlah argumen yang dimasukkan benar atau tidak. 
* ```if(argc != 5) ```
ika jumlah argumen benar maka akan diperiksa apakah argumen jam yang dimasukkan benar atau tidak dengan mengubah argumen tersebut menjadi int dan memeriksanya. 
*``` a = atoi(argv[1]); if(a > 59 || a < 0); failure();```

Jika salah akan menjalankan fungsi failure yang berarti akan keluar. Setelah diperiksa dan argumen semuanya benar maka argumen tersebut akan diassign di variable baru yaitu dettime, mentime, dan jamtime yang nantinya formatnya akan dirumah menjadi %02d yang artinya jika string tersebut kurang dari 10 atau hanya satuan maka akan ditambahkan angka 0 pada string tersebut.
*```sprintf(dettime,"%02d\n", a);```
Selanjutnya akan didapatkan local time dari komputer dengan menggunakan tm_t dan dari situ akan diassign lagi variable local_time kedalam buffdet, buffmen, dan buffjam yang berarti ketiga variable tersebut berisi waktu sekarang dan akan diupdate seterusnya. 
*```strftime(buffdet,30,"%S", info);```
Setelah jam lokal didapat maka bisa dibandingkan semua variable tersebut seperti apakah jam sekarang sama dengan argumen atau argumen merupakan bintang. Jika bintang maka akan dilaksanakan setiap waktu. Lalu dengan perbandingan tersebut didapatkan dilakukan pengecekan.
*```s1 = strcmp(dettime, buffdet);```
*```b1 = strcmp(argv[1], "*");```
Setelah di compare selanjutnya akan membandingkan dengan argumen kapan akan dijalakan dan dieksekusi bashnya dengan membuat child baru lalu menjalankan fungsi eksekusi.
*```if(b1 == 0 && b2 == 0 && b3 == 0) pid_t child_id; child_id = fork(); if (child_id == 0); execution(path);```


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
  FILE *fp = fopen("killer.sh", "w+");
  if(code == 0)
  {
    fprintf(fp, "#!/bin/bash\n");
    fprintf(fp, "kill -9 %d \n", pid);
    fprintf(fp, "rm -- \"$0\"");

    fclose(fp);
  }

  else if(code == 1)
  {
    fprintf(fp, "#!/bin/bash\n");
    fprintf(fp, "kill -15 %d \n", pid);
    fprintf(fp, "rm -- \"$0\"");

    fclose(fp);

  }

  else
  {
    exit(EXIT_FAILURE);
  }

  pid_t child_id;
  child_id = fork();

   if (child_id < 0)
     exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti

   if (child_id == 0) {
     // this is child
   }

   else {
     // this is parent
     char *argv[] = {"bash", "killer.sh", "/home/farrelmt/", NULL};
     execv("/bin/bash", argv);
   }
}

int main(int argc, char *argv[])
{
  //Generate Program Killer
  pid_t pid, sid;        // Variabel untuk menyimpan PID
  pid = fork();     // Menyimpan PID dari Child Process
  int killpid = getpid();

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

  while (1)
  {
    char folder_name[80] = "/home/farrelmt/";
    char temp[30];
    time_t rawtime;
    struct tm *info;
    int status;

    pid_t child_a, child_a2, child_b, child_c;

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
      for(int i=0;i<20;i++)
      {
        child_b = fork();

        if(child_b == 0)
        {
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

        if(i == 19)
        {
          // NO 2C - ZIP FOLDER & DELETE
          child_c = fork();
          char zip_name[50];
          strcpy(zip_name, temp);
          strcat(zip_name, "/");

          if(child_c == 0)
          {
            char *argv[] = {"rm", "-r", temp, NULL};
            execv("/usr/bin/rm", argv);
          }

          else
          {
            //char *argv[] = {"zip", temp, "-r", "-m", zip_name, NULL};
            //execv("/usr/bin/zip", argv);
          }
        }
        sleep(5);
      }

      waitpid(child_b, &status, 0);

      int code = 0;

      if(argc == 1)
      {
        if(strcmp(argv[1], "-a") == 0)
          code = 0;
        else if(strcmp(argv[1], "-b") == 0)
          code = 1;
        else
          exit(EXIT_FAILURE);
      }

      else
      {
        exit(EXIT_FAILURE);
      }

      genKillProgram(killpid, code);

    }
    sleep(30);
  }
}

```

* ```char *argv[] = {"mkdir", folder_name, NULL}; execv("/bin/mkdir", argv);```  [Membuat directori per 30 detik]
* ```strcat(url, file_size); ``` [Mendownload gambar sesuai URL]
* ```char *argv[] = {"wget", url, "-O", file_path, NULL}; execv("/usr/bin/wget", argv);``` [Mendownload gambar dengan format tertentu per 5 detik]
* ```strcat(file_path, file_name);``` [Mendapatkan lokasi download]
* ```time (&rawtime); info = localtime(&rawtime); strftime(file_name, 30, "%Y-%m-%d_%X", info);```[Mendapatkan waktu lokal]	
* ```char *argv[] = {"wget", url, "-O", file_path, NULL}; execv("/usr/bin/wget", argv);```[Mendownload dari link char]
* ```char zip_name[50]; strcpy(zip_name, temp); strcat(zip_name, "/"); char *argv[] = {"zip", temp, "-r", "-m", zip_name, NULL}; execv("/usr/bin/zip", argv); ```[Melakukan zip pada file]
* ```char *argv[] = {"rm", "-r", temp, NULL}; execv("/usr/bin/rm", argv);```  [Menghapus directori beserta isinya]
* ``` if(strcmp(argv[1], "-a") == 0); else if(strcmp(argv[1], "-b") == 0);```  [Memeriksa argumen apakah -a atau -b]
* ```genKillProgram(pid, code);```  [Menjalankan fungsi yang akan membuat program killer dan menghapus program itu sendiri]

KENDALA :
c. zip file
e. meneksekusi killer seusai argument
	
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
  <img src="https://imgur.com/fl39UBF.png" width="350" title="1">
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
