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
