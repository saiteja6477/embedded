#include<stdio.h>
#include<unistd.h>

int main() {
   int p[2];
   int returnstatus;
   int pid;
   char writemessages[2][20]={"hey", "hi"};
   char readmessage[20];
   returnstatus = pipe(p);
   
   pid = fork();
   
   // child process
   if (pid == 0) {
      read(p[0], readmessage, sizeof(readmessage));
      printf("child process reading 1 is %s\n", readmessage);
      read(p[0], readmessage, sizeof(readmessage));
      printf("child process reading 2 is %s\n", readmessage);
   } else { //parent process
      printf("parent process writing 1 is %s\n", writemessages[0]);
      write(p[1], writemessages[0], sizeof(writemessages[0]));
      printf("parent process writing 2 is %s\n", writemessages[1]);
      write(p[1], writemessages[1], sizeof(writemessages[1]));
   }
   return 0;
}