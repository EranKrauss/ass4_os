#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"


void
write_blocks(int fd, int num_of_blocks, char* buf){
    int written;
    int i;
    int printcount = 0;
    for(i = 0; i < num_of_blocks; i++, printcount++){
    written = write(fd, buf, sizeof(buf));
    if(printcount == 255){
      printf("iteration %d completed\n", i);
      printcount = 0;
    }
    if(written < 0){
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
  char* name = "sanity_check.txt";
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
  printf("finished writing 12KB (direct)\n");
  write_blocks(fd, 256, buf);
  printf("finished writing 268KB (single indirect)\n");
  write_blocks(fd, 256*256, buf);
  printf("finished writing 10MB (double indirect)\n");
  unlink(name);
  close(fd);
  exit(0);
}