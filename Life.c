//Vincent Lai
//Life.c



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


typedef struct parameters{
        int i;
        int j;
    }arguments;
    
int **newGrid;
int **startGrid;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* nextGen(void *theArguments){
    
    
    arguments *args = theArguments;
    
    int i = args->i;
    int j = args->j;
    
    int ones = 0;
    
    ones += startGrid[i-1][j];
    ones += startGrid[i][j-1];
    ones += startGrid[i-1][j-1];
    ones += startGrid[i+1][j];
    ones += startGrid[i][j+1];
    ones += startGrid[i+1][j+1];
    ones += startGrid[i+1][j-1];
    ones += startGrid[i-1][j+1];
    
    pthread_mutex_lock(&mutex);
    if ((startGrid[i][j] == 1) && (ones == 2  || ones == 3)){
        newGrid[i][j] = 1;
    } else if ((startGrid[i][j] == 1) && (ones < 2 || ones > 3)){
        newGrid[i][j] = 0;
    } else if ((startGrid[i][j] == 0) && (ones == 3)){
        newGrid[i][j] = 1;
    } else if ((startGrid[i][j] == 0) && (ones < 3 || ones > 3)){
        newGrid[i][j] = 0;
    }
    pthread_mutex_unlock(&mutex);
    //exit
    
    pthread_exit(0); 
}


int main(int argc, char *argv[]){
    
    //printf("Step1\n");
    
    FILE *fp = fopen(argv[2], "r");
    
    //printf("Step2\n");
    
    int m;
    int n;
    
    fscanf(fp, " %d", &m);
    fscanf(fp, " %d", &n);
    
    //printf("Step3\n");
    
    startGrid = (int**)malloc(sizeof(int *)*(m+2));
    for (int i = 0; i < m+2; i++){
        startGrid[i] = (int *)malloc(sizeof(int)*n);
    }
    
    for(int i = 0; i < m+2; i++){
        for(int j = 0; j < n+2; j++){
            startGrid[i][j] = 0;
        }
    }
    
   // printf("Step4\n");
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            fscanf(fp, " %d", &startGrid[i+1][j+1]);
        }
    }
    
    printf("Starting:\n");
    for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                printf("%d ", startGrid[i+1][j+1]);
            }
            printf("\n");
        }
    
   // printf("Step5\n");
   
    
    newGrid = (int**)malloc(sizeof(int *)*(m+2));
    for (int i = 0; i < m+2; i++){
        newGrid[i] = (int *)malloc(sizeof(int)*n);
    }
    
    for(int i = 0; i < m+2; i++){
        for(int j = 0; j < n+2; j++){
            newGrid[i][j] = 0;
        }
    }
    
    //printf("Step6\n");
    
    pthread_t thread_id[m*n];
    
    int gens = atoi(argv[1]);
    
    //printf("Step7\n");
    
    
    
    for (int generations = 0; generations < gens; generations++){
        
        //sem_init(&mutex, 0, 1);
    
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                
                //printf("Step7.1\n");
                
                arguments *args = (arguments *)malloc(sizeof(arguments));
                args->i = i+1;
                args->j = j+1;
                
                //printf("Step7.2\n");
                
                int threadNum = j+(n*(i));
                pthread_create(&thread_id[threadNum], NULL, nextGen, (void *)(args));
                
                //printf("Step7.3\n");
            }
        }
        
        //printf("Step8\n");
        
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                //printf("Step8.1\n");
                int threadNum = j+(n*(i));
                //printf("Step8.2\n");
                pthread_join(thread_id[threadNum], NULL);
                //printf("Step8.3\n");
            }
        }
        //sem_destroy(&mutex);
        
        //printf("Step9\n");
        
        int newGen = generations+1;
        
        printf("Generation %d:\n", newGen);
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                printf("%d ", newGrid[i+1][j+1]);
            }
            printf("\n");
        }
        
        for (int i = 0; i < m + 2; i++){
            for (int j = 0; j < n + 2; j++){
                startGrid[i][j] = newGrid[i][j];
            }
        }
        printf("\n");
    }
    //for (int i = 0; i < m+2; i++){
        //free(newGrid[i]);
    //}
    //free(newGrid);
    //for (int i = 0; i < m+2; i++){
        //free(startGrid[i]);
    //}
    //free(startGrid);
}