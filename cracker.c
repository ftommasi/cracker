#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

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

void tester(){
  
//  const int guess_size = 8;
  const char allowed_alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  const unsigned int allowed_alphabet_size = 26;
  
  int i,j,guess_size;
  for(guess_size = 1; guess_size < 9; guess_size++){
    char attempt[guess_size+1];
    int temp = 0;
    attempt[guess_size] = '\0'; 
    while(attempt[temp] != '\0'){ attempt[temp] = 'a'; temp++; }    
    for(i = guess_size-1; i  > -1; i-- ){
      for(j=0; j < allowed_alphabet_size; j++){
        attempt[i] = allowed_alphabet[j];
        printf("i:%d j:%d letter:%c\n%s\n",i,j,allowed_alphabet[j],attempt);
      }
    }
  }
}

char* recursive(int length){
  if(length < 1) return('\0');
 
  const char allowed_alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  const unsigned int allowed_alphabet_size = 26;
  int j;
  char attempt [length+1];
  attempt[length] = '\0';
  for(j=0; j < allowed_alphabet_size; j++){
    attempt[length-2] = allowed_alphabet[j];
  attempt[length-1] = recursive(allowed_alphabet-1)ASD<J>NB fv yhui;

  }
  
  printf("%s",attempt);
  return attempt;

}



int main(int argc, char** argv){
  
  printf("FINAL RESULt: %s\n",recursive(8));

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
return 0;ASD<J>NB fv yhui}
