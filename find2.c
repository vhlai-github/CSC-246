/*
Vincent Lai find2.c
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>


char word[100];
    
typedef struct parameters{
        char file[100];
        int argIndex;
    }arguments;

void* compareToFile(void *theArguments){
    
    arguments *args = theArguments;
    //open file
    FILE *fp = fopen(args->file, "r");
    //check file line by line
            
            
    int c;
    int index = 0;
    int line = 1;
    int i = args->argIndex;
    char currWord[200];
            
    while((c = fgetc(fp)) != EOF){
    //printf("%c", c);
        if (c == '\r'){
            currWord[index] = '\0';
                    
            //printf("%s \n", currWord);
            if (strcmp(word, currWord) == 0){
                printf("File: %d Line: %d\n", i-1, line);
            }
            line++;
            index = 0;
            c = fgetc(fp);
        }else if (c == '\n'){
            currWord[index] = '\0';
                    
            //printf("%s \n", currWord);
            if (strcmp(word, currWord) == 0){
                printf("File: %d Line: %d\n", i-1, line);
            }
            line++;
            index = 0;
        } else if (c == ' '){
            currWord[index] = '\0';
                    
            //printf("%s \n", currWord);
            if (strcmp(word, currWord) == 0){
                printf("File: %d Line: %d\n", i-1, line);
            }
            
            index = 0;
        } else {
                //printf("%s\n", currWord);
                currWord[index] = c;
                index++;
        }
    }
    currWord[index] = '\0';
                    
    //printf("%s \n", currWord);
    if (strcmp(word, currWord) == 0){
        printf("File: %d Line: %d\n", i-1, line);
    }
    free(args);
    //exit
    pthread_exit(0); 
}


int main(int argc, char *argv[]){
    
    strcpy(word, argv[1]);
    
    //length = strlen(argv[1]) + 1;
    //printf("0");

    pthread_t thread_id[argc-2];
    
    for (int i = 2; i < argc; i++){
        
        arguments *args = (arguments *)malloc(sizeof(arguments));;
        strcpy(args->file, argv[i]);
        args->argIndex = i;
                
        pthread_create(&thread_id[i], NULL, compareToFile, (void *)(args));
    }
    
    for (int i = 2; i < argc; i++){
        pthread_join(thread_id[i], NULL);
    }
}
