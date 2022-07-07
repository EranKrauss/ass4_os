#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  char* s = "-s";
  if((argc != 3 || (argc == 3 && strcmp(argv[1], s) == 0)) && (argc != 4 || (argc == 4 && strcmp(argv[1], s) != 0))){
    exit(1);
  }
  if(argc == 3){
    if(link(argv[1], argv[2]) < 0)
      fprintf(2, "link Failed\n");
  } else{
    if(symlink(argv[2], argv[3]) < 0){
      fprintf(2, "symbolic link Failed\n");
      exit(1);
    }
  }
  exit(0);
}
