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
        exit(EXIT_FAILURE);
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
        exit(EXIT_FAILURE);
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
        exit(EXIT_FAILURE); 
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
        exit(EXIT_FAILURE);
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
        exit(EXIT_FAILURE);
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
        exit(EXIT_FAILURE);
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
        exit(EXIT_FAILURE);
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
