#define _GNU_SOURCE 
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>

struct recurse_arg{
  char* target;
  char* current;
  int index;  
  int length;
  int thread_number;
  char start;
  char end;
  int num_threads;
  int loopsize;
} ;


 struct crypt_data data;

void* recursive(char* target,char* current,int index, int length, int start,int end){
  const char allowed_alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  const unsigned int allowed_alphabet_size = 26;
  
  if(length < 1 ){
    char* end = '\0';
    char salt[3];
    strncpy(salt,target,2);
    salt[2] = '\0';
    char* crypted_attempt = crypt_r(current,salt,&data);
    printf("%s => %s vs %s\n",current,crypted_attempt,target);
    if(!strcmp(crypted_attempt,target)){
      printf("I FOUND THE PASS AND IT IS %s\n",current);
      exit(0);
    }
    return;
  }
  
  else{
    int i;
    for(i=start; i < end; i++ ){
      current[index] = allowed_alphabet[i]; 
      recursive(target,current,index+1,length-1,0,allowed_alphabet_size);
    }
   return; 
  }

}

void* threaded_recurse(void* args){
  struct recurse_arg* arg = (struct recurse_arg*) args;
  const char allowed_alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  const unsigned int allowed_alphabet_size = 26;
  char current[256];
  char target[256];
  strcpy(current,arg->current);
  strcpy(target,arg->target);
  int chunk_size = allowed_alphabet_size/arg->num_threads;
  int thread_start = arg->thread_number * (chunk_size+1);
  int thread_finish = arg->thread_number+1 * (chunk_size);
  thread_finish = ((thread_finish > allowed_alphabet_size) ? allowed_alphabet_size : thread_finish);
  int i;
  for(i=0;i<arg->loopsize;i++){
    recursive(target,current,arg->index,i,thread_start,thread_finish);
  }
}

int main(int argc, char** argv){
  
  data.initialized = 0;
  if(argc != 4){
    printf("Error: Wrong number of input args\n  Usage: crack <threads> <keysize> <target>\n");
    return -1;
  }

  if(atoi(argv[2]) > 9 || atoi(argv[2]) < 1){
    printf("Incorrect key size. Keysize should be 8\nUsage: crack <threads> <keysize> <target>\n");
    return -1;
  }

  char* string = (char*)malloc(256*sizeof(char));
  char * empty = "";
  strcat(string,empty);
  char target[256];
  pthread_t pthreads[atoi(argv[1])];

  int i;
#if 0
  for(i =0; i<atoi(argv[2]); i++)
   recursive(argv[3],string,0,i,8,16);
 exit(0); 
#endif

  for(i=0;i<atoi(argv[1]);i++){
    struct recurse_arg arg;
    char  temp1[256];
    char temp2[256];

    arg.target = argv[3];
    arg.current = string;
    arg.index=1;
    arg.length=5;
    arg.thread_number = i;
    arg.num_threads = atoi(argv[1]);
    arg.loopsize = atoi(argv[2]);
    pthread_create(&pthreads[i],NULL,threaded_recurse,(void*)&arg);
  }

 for(i=0;i<atoi(argv[1]);i++){
    pthread_join(pthreads[i],NULL);
  }

  free(string);
  return 0;
}


