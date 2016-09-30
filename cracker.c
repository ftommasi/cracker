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

} ;





void* recursive(char* target,char* current,int index, int length, int start,int end){
  const char allowed_alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  const unsigned int allowed_alphabet_size = 26;
  
  if(length < 1 ){
    char* end = '\0';
    char salt[3];
    strncpy(salt,target,2);
    salt[2] = '\0';
    char* crypted_attempt = crypt(current,salt);
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
 struct recurse_arg* arg;
  const char allowed_alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  const unsigned int allowed_alphabet_size = 26;
  
  int num_threads = arg->num_threads;
  int chunks = allowed_alphabet_size/num_threads;
  int thread_start = arg->thread_number * (chunks-1);
  int thread_finish = arg->thread_number * (chunks);
  
  printf("chunks %d size %d start %d finish",chunks,allowed_alphabet_size,thread_start,thread_finish);
  recursive(arg->target,arg->current,arg->index,arg->length,thread_start,thread_finish);

}

int main(int argc, char** argv){
  char* string = (char*)malloc(256*sizeof(char));
  char * empty = "";
  strcat(string,empty);
  char target[256];
  pthread_t pthreads[atoi(argv[1])];

  int i;
  for(i=1; i < atoi(argv[2])+1; i++){
    recursive(argv[3],string,0,i,0,4);
    printf("Nothing for length %d\n",i);
  }

  if(argc != 3){
    printf("Error: Wrong number of input args\n  Usage: crack <threads> <keysize> <target>\n");
    return -1;
  }

  if(atoi(argv[2]) > 8 || atoi(argv[2]) < 1){
    printf("Incorrect key size. Keysize should be 8\nUsage: crack <threads> <keysize> <target>\n");
    return -1;
  }

    
  
  
  for(i=0;i<atoi(argv[1]);i++){
    const char allowed_alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    const unsigned int allowed_alphabet_size = 26;
    struct recurse_arg* arg;
    
    arg->target = argv[3];
    arg->current = allowed_alphabet[allowed_alphabet_size/i];
    arg->index=1;
    arg->length=5;
    arg->thread_number = i+1;
    //printf("Thread %d is starting at char %c\n",i,allowed_alphabet_size/i);
    pthread_create(&pthreads[i],NULL,threaded_recurse,NULL);
  }

 for(i=0;i<atoi(argv[1]);i++){
    pthread_join(pthreads[i],NULL);
  }

  free(string);
  return 0;
}


