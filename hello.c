#include<stdio.h> // define the header file  
#include<stdlib.h>
#include<pthread.h>

int thread_count = 0;

void *Hello(void* rank){
    long my_rank = (long) rank;
    printf("Hello %1d , %d \n",my_rank,thread_count);
    return NULL;
}
void main(int argc, char* argv[])   // define the main function  
{  
    long thread;
    pthread_t* thread_handles;

    thread_count = strtol(argv[1],NULL,10);

    thread_handles =  malloc(thread_count*sizeof(pthread_t));

    for(thread = 0; thread < thread_count;thread++){
        pthread_create(&thread_handles[thread],NULL,Hello, (void*) thread);
    }
    printf("ho ho \n");
    for(thread = 0; thread < thread_count;thread++){
        pthread_join(thread_handles[thread],NULL);
    }

    free(thread_handles);

    
}  
