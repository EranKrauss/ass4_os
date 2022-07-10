#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"


void
write_blocks(int fd, int num_of_blocks, char* buf){
    int isWritten;
    int i;
    int num_of_print = 0;
    for(i = 0; i < num_of_blocks; i++, num_of_print++){
    isWritten = write(fd, buf, sizeof(buf));
    if(num_of_print == 255){
      printf("iteration %d completed\n", i);
      num_of_print = 0;
    }
    if(isWritten < 0){
        printf("failed writing direct block number %d\n", i);
        exit(1);
    }
  }
}


void
main(int argc, char *argv[])
{
  int fd;
  char buf[1024];
  char* name = "sanity_test.txt";
  int i;
  for(i=0; i<1024; i++){
      buf[i] = '0';
  }
  fd = open(name, O_CREATE | O_RDWR);
  if(fd < 0){
      printf("failed opening file\n");
      exit(1);
  }
  write_blocks(fd, 12, buf);
  printf("Finished writing 12KB (direct)\n");
  write_blocks(fd, 256, buf);
  printf("Finished writing 268KB (single indirect)\n");
  write_blocks(fd, 256*256, buf);
  printf("Finished writing 10MB (double indirect)\n");
  unlink(name);
  close(fd);
  exit(0);
}