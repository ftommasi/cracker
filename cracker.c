#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>



void recursive(char* target,char* current,int index,  int length){
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
    for(i=0; i < allowed_alphabet_size; i++ ){
      current[index] = allowed_alphabet[i]; 
      recursive(target,current,index+1,length-1);
    }
   return; 
  }

}

void* threaded_recurse(void* args){
  recursive()
}

int main(int argc, char** argv){
  if(argc != 3){
    printf("Error: Wrong number of input args\n  Usage: crack <threads> <keysize> <target>\n");
    return -1;
  }

  if(atoi(argv[2]) > 8 || atoi(argv[2]) < 1){
    printf("Incorrect key size. Keysize should be 8\nUsage: crack <threads> <keysize> <target>\n");
    return -1;
  }

  char* string = (char*)malloc(256*sizeof(char));
  char * empty = "";
  strcat(string,empty);
  char target[256];
  pthread_t pthreads[atoi(argv[1])];
  int i;
  void* args;
  for(i=0;i<atoi(argv[1]);i++){
    pthread_create(&pthreads[i],NULL,threaded_recurse,args);
  }
  
  for(i=1; i < atoi(argv[2]); i++){
    recursive(argv[3],string,0,i);
    printf("Nothing for length %d\n",i);
  }
 for(i=0;i<atoi(argv[1]);i++){
    pthread_(&i);
  }

  free(string);
  return 0;
}


