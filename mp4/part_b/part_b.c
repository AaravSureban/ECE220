#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef WORD_CHARS
#define WORD_CHARS 6
#define WSIZE 2315
#endif

extern const int DLEN;
extern unsigned long ihash(int num);
extern unsigned long shash(char *str);
extern char words[WSIZE][WORD_CHARS];
char file_hash[65] = {0};
long uin = -1;

char release_hash[65] = "438e3e73b5959b5182cf1b1f63d78cb897037b233b6bc67fd472475006ad3769";
int file_unchanged = 0;

int check_three(long seed, char *w1, char *w2, char *w3){
  int nums[3] = {-1};
  int flag = 1; 
  char *arg_words[3]= {w1, w2, w3};

  for (int i=0; i<3; i++)
    nums[i] = rand() % DLEN;

  for (int i=0; i<3; i++)
    if (ihash(nums[i]) != shash(arg_words[i]))
      flag = 0; 

  if (flag){
    printf("Passed passphrase check!\n");
    printf("Preparing test file.\n");
    FILE *fptr = fopen("testdata", "w");
    fprintf(fptr, "%ld\n", uin);
    
    for(int i=0; i<3; i++)
      fprintf(fptr, "%d\n", nums[i]);

    for(int i=0; i<3; i++)
      fprintf(fptr, "%s\n", arg_words[i]);
    
    fclose(fptr);
    return 0;
  }
  else{
    printf("Failed passphrase check: %d, %d, %d\n", nums[0], nums[1], nums[2]);
    return -1;
  }
}

void check_file_integrity(char *argv[]){
  char cmd[256] = {0};
  FILE *in=NULL;
  char *cur_file = realpath(argv[0], NULL);

  sprintf(cmd, "bash -c \"objdump -d %s | tail -n +4 | awk '{print $1}' | sha256sum\"", cur_file);
  free(cur_file);
  in = popen(cmd, "r");
  if (in == NULL){
    fprintf(stderr, "Error running command\n");
    exit(1);
  }

  fgets(file_hash, sizeof(file_hash), in);
  pclose(in);

  if ( getenv("DEBUG") != NULL && strcmp(getenv("DEBUG"), "1") == 0){
    printf("Hash: %s\n", file_hash);
  }

  if (strcmp(file_hash, release_hash) != 0) {
    file_unchanged = 0;
  } else {
    file_unchanged = 1;
  }
}

#ifndef MAIN
#define MAIN
int main(int argc, char *argv[]){
  long seed=-1;

  if (argc!=4){
    fprintf(stderr, "Please enter exactly three arguments!\n");
    return -1;
  }

  check_file_integrity(argv);

  printf("Please enter your UIN:\t");
  scanf("%ld", &uin);
  seed = uin;
  for (int i=0; i<sizeof(file_hash); i++){ seed += file_hash[i]; }
  srand(seed);

  switch (argc){
    case 4:
      check_three(seed, argv[1], argv[2], argv[3]);
      break;

    default:
      fprintf(stderr, "Please enter exactly three arguments!\n");
  }

  if (!file_unchanged) {
    fprintf(stderr, "File has been changed since release and will not output correct results.\n");
    fprintf(stderr, "Please restore the original file.\n");
    return -1;
  }

  return 0;
}
#endif /* ifndef MAIN */
