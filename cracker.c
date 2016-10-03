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
  int num_threads;
  int loopsize;
  pthread_mutex_t m;
} ;



 char* guessess[256];

void* recursive(char* target,char* current,int index, int length, int start,int end,struct crypt_data* data){
  const char allowed_alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  const unsigned int allowed_alphabet_size = 26;
  
  if(length < 1 ){
    char* end = '\0';
    char salt[3];
    strncpy(salt,target,2);
    salt[2] = '\0';
    char* crypted_attempt = crypt_r(current,salt,data);
  //  printf("%s => %s vs %s\n",current,crypted_attempt,target);
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
      char current_test[256];
      unsigned int index_test = index+1;
      unsigned int length_test = length-1;

      index_test = ((index_test > allowed_alphabet_size) ? allowed_alphabet_size : index_test);

      length_test= ((index_test < 0) ? 0 : length_test);
      strcpy(current_test,current);

      recursive(target,current,index_test,length_test,0,allowed_alphabet_size,data);
    }
   return; 
  }

}

void* threaded_recurse(void* args){
  
  struct recurse_arg* arg = (struct recurse_arg*) args;
  struct crypt_data data; 
  data.initialized = 0;
  const char allowed_alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  const unsigned int allowed_alphabet_size = 26;
  guessess[arg->thread_number] = (char*)malloc(256*sizeof(char));
  
  int chunk_size = allowed_alphabet_size/arg->num_threads;
  int thread_start =((arg->thread_number) * (chunk_size));
  int thread_finish = ((arg->thread_number+1) * (chunk_size))+2;
  //printf("%d: %d - %d\n",arg ->thread_number,thread_start, thread_finish);
  thread_finish = 
    ((thread_finish > allowed_alphabet_size) ? allowed_alphabet_size : thread_finish);
  
  int i;
  for(i=0;i<arg->loopsize;i++){
    //int lock = pthread_mutex_lock(&arg->m);
    //printf("ATTEMPTING FROM %c to %c in thread %d\n",allowed_alphabet[thread_start],allowed_alphabet[thread_finish],arg->thread_number);
    recursive(arg->target,guessess[arg->thread_number] ,arg->index,i,thread_start,thread_finish,&data);
    //int unlock = pthread_mutex_unlock(&arg->m);
  }
  return NULL;
}

int main(int argc, char** argv){
  pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
//  data.initialized = 0;
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
  struct recurse_arg* args[atoi(argv[1])];
  char strings[atoi(argv[1])];
  int i;
#if 0
  for(i =0; i<atoi(argv[2]); i++)
   recursive(argv[3],string,0,i,8,16);
 exit(0); 
#endif

  for(i=0;i<atoi(argv[1]);i++){
    struct recurse_arg* arg = 
      (struct recurse_arg*)malloc(sizeof(struct recurse_arg));
    char* current = (char*)malloc(sizeof(char)*256);
    strings[i] = current;
    args[i] = arg; 
    char  temp1[256];
    char temp2[256];
    arg->current = current; 
    arg->target = argv[3];
    arg->index=0;
    arg->length=atoi(argv[1]);
    arg->thread_number = i;
    arg->num_threads = atoi(argv[1]);
    arg->loopsize = atoi(argv[2]);
    arg->m =m;
    pthread_create(&pthreads[i],NULL,threaded_recurse,(void*)arg);

  }

 for(i=0;i<atoi(argv[1]);i++){
   pthread_join(pthreads[i],NULL);
   free(strings[i]);
   free(args[i]); 
  }

  free(string);
  return 0;
}


