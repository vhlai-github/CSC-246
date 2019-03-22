/*
Vincent Lai find.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
    
    //int l = strlen(argv[0])+1;
    //char word[l] = argv[0];
    
    
    for (int i = 2; i < argc; i++){
        //printf("%s\n", argv[1]);
        int id = -2;
        id = fork();
        if (id == 0){
            
            //int file = i;
            //open file
            FILE *fp = fopen(argv[i], "r");
            //check file line by line
            
            
            int c;
            int index = 0;
            int line = 1;
            char currWord[200];
            
            while((c = fgetc(fp)) != EOF){
                //printf("%c", c);
                if (c == '\r'){
                    currWord[index] = '\0';
                    
                    //printf("%s \n", currWord);
                    if (strcmp(argv[1], currWord) == 0){
                        printf("File: %d Line: %d\n", i-1, line);
                    }
                    line++;
                    index = 0;
                    c = fgetc(fp);
                } else if (c == '\n'){
                    currWord[index] = '\0';
                    
                    //printf("%s \n", currWord);
                    if (strcmp(argv[1], currWord) == 0){
                        printf("File: %d Line: %d\n", i-1, line);
                    }
                    line++;
                    index = 0;
                } else if (c == ' '){
                    currWord[index] = '\0';
                    
                    //printf("%s \n", currWord);
                    if (strcmp(argv[1], currWord) == 0){
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
            if (strcmp(argv[1], currWord) == 0){
                 printf("File: %d Line: %d\n", i-1, line);
            }
            //exit
            exit(0);
        }
    }
    for (int j = 2; j < argc; j++){
        wait(NULL);
    }
}