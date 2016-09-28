#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

char* crack(char * target, int attempt_size ){
  //the goal is to go through all attempts for given attempt_size such that
  //  attempt -> crypt() == target
  //  store result into password
  if(attempt_size < 1) return '\0'; //TODO(Fausto): what should the base case return?

  const char allowed_alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  const unsigned int allowed_alphabet_size = 26;
  int i,j;
  
    char attempt[attempt_size];
  for(i=0; i < attempt_size; i++ ){
    for(j=0; j< allowed_alphabet_size; j++){
      //TODO(Fausto): verify salt logic
      
      //append first two characters of target as salt i
      //strcat(attempt,allowed_alpahbet[j]);
      //strcat(attempt,crack(target,attempt_size-1));
      
    }
  }
  
  char* salt;
  strcat(salt,target[0]);
  strcat(salt,target[1]);
  //encrypted_attempt = crypt(attempt,salt);
  return attempt;
      
}

void tester(int length){
  if(length < 1) return('\0');
  
  const char allowed_alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  const unsigned int allowed_alphabet_size = 26;
  
    int i,j,k;
    char attempt [length+1];
    attempt[length] = '\0';
    initialize_string(attempt,'a');
    for(k=0; k< length; k++){
      for(i=length-1; i > -1; i--){
        for(j=0; j < allowed_alphabet_size+1; j++){
          attempt[i] = allowed_alphabet[j%allowed_alphabet_size];
          printf("%s\n",attempt);
        }
      }
    }
    return attempt;

}

void initialize_string(char* string, const char value){
  int i =0;
  while(string[i] !='\0'){
    string[i] = value; 
    i++;
  }
}

char* bruteforce(){
  const char allowed_alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  const unsigned int allowed_alphabet_size = 26;

}


void recursive(char* current, int length){
  printf("entered recursive\n"); 
  const char allowed_alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  const unsigned int allowed_alphabet_size = 26;
  
  if(length < 1 ){
    printf("basecase\n");
    char* end = '\0';
    //strcat(current,end);
    printf("%s\n",current);
    return;
  }
  
  else{
    int i;
    for(i=0; i < allowed_alphabet_size; i++ ){
      char* letter = allowed_alphabet[i];
      strcat(current,letter);
      printf("past cat\n");
      recursive(current,length-1);
    }
   return; 
  }

}




int main(int argc, char** argv){
  char* string = (char*)malloc(10*sizeof(char));
  char * empty = "";
  strcat(string,empty);
  recursive(string,2);
  //printf("FINAL RESULt: %s\n",recursive(3));

  if(argc != 3){
    printf("Error: Wrong number of input args\n  Usage: crack <threads> <keysize> <target>\n");
    return -1;
  }
  
  if(atoi(argv[2]) > 8 || atoi(argv[2]) < 1){
    printf("Incorrect key size. Keysize should be 8\nUsage: crack <threads> <keysize> <target>\n");
    return -1;
  }
  
  /*char password[256];
  int found_password = crack(argv[1],argv[2],password);
  
  if(found_password){
    printf("The password is: %s\n",password);
  }
  else{
    printf("Password could not be found\n");
  }
*/
  free(string);
  return 0;
}


