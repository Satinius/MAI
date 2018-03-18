#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/sysinfo.h>
#include <sys/stat.h>
#include <inttypes.h>
#include <sys/types.h>
#include <unistd.h>
#include <syslog.h>
#include <fcntl.h>


void StatPrint(struct stat fileStat);


int main()
{


  const char msg[] = "This programm is test different system calls\n";
  write(STDOUT_FILENO, msg, sizeof( msg ) - 1 );
  
  if(mkdir("mydir", S_IRWXU | S_IRWXG | S_IRWXO))
    fprintf(stderr, "%s\n", "Failure");
  else 
    fprintf(stdout, "%s\n", "Directory create successfully");


  if(rmdir("mydir"))
    fprintf(stderr, "%s\n", "Failure");
  else 
    fprintf(stdout, "%s\n", "Directory remove successfully");

  struct sysinfo th;

  if(sysinfo(&th)){
    fprintf(stderr, "%s\n", "Failure");
  }
  else {
    fprintf(stdout, "%s\n", "Sysinfo get successfully");
        
        
    FILE *f = fopen("idn", "w");
    if(f) {
      fprintf(f, "uptime: %ld\n", th.uptime);
      //fprintf(f, "loads average: 1m-%lu 5m-%lu 15m-%lu\n", th.loads[0], th.loads[1], th.loads[2]);
      //fprintf(f, "Total ram: %lu\n", th.totalram);
      fprintf(f, "Free ram: %lu\n", th.freeram);
      //fprintf(f, "Shared ram: %lu\n", th.sharedram);
      //fprintf(f, "Procs: %hu\n", th.procs);
    }else 
      fprintf(stderr, "%s\n", "Failure");
    fclose(f);
        char buf[128];
        int fd1 = open("idn", O_WRONLY);
        if (fd1 == -1) {
            fprintf(stderr, "%s\n", "Open file idn failure");
        }else {
            scanf("%127s", buf);
            write(fd1, buf, strlen(buf));
            close(fd1);
        }
  }   

  if(rename("idn", "new"))
    fprintf(stderr, "%s\n", "Failure");
  else 
    fprintf(stdout, "%s\n", "File rename successfully");

  struct stat myFile;
  if(stat("new", &myFile))
    fprintf(stderr, "%s\n", "Failure");
  else {
    fprintf(stdout, "%s\n", "Get file stat successfully");
    //StatPrint(myFile);
  }

  setlogmask (LOG_UPTO (LOG_NOTICE));

  openlog ("exampleprog", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

  syslog (LOG_NOTICE, "Program started by User %d", getuid ());
  syslog (LOG_INFO, "A tree falls in a forest");

  closelog ();



  int child_id;
  child_id = fork();
  if (child_id)
    fprintf(stdout, "I'm the parent: %ld and parent: %ld\n", (intmax_t)getpid(), (intmax_t)getppid());
  else
    fprintf(stdout, "I'm the child: %ld and parent: %ld\n", (intmax_t)getpid(), (intmax_t)getppid());


  exit(0);
}



void StatPrint(struct stat fileStat)
{
    fprintf(stdout, "File Size: \t\t%d bytes\n",fileStat.st_size);
    fprintf(stdout, "Number of Links: \t%d\n",fileStat.st_nlink);
    fprintf(stdout, "File inode: \t\t%d\n",fileStat.st_ino);
 
    fprintf(stdout, "File Permissions: \t");
    fprintf(stdout,  (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    fprintf(stdout,  (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    fprintf(stdout,  (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    fprintf(stdout,  (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    fprintf(stdout,  (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    fprintf(stdout,  (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    fprintf(stdout,  (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    fprintf(stdout,  (fileStat.st_mode & S_IROTH) ? "r" : "-");
    fprintf(stdout,  (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    fprintf(stdout,  (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    fprintf(stdout, "\n\n");

}