#include<stdio.h> // define the header file  
#include<stdlib.h>
#include<pthread.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>


struct Node {
    int data;
    struct Node* next;
};

struct Node* head = NULL;
int n;
int m;
float member_fraction, insert_fraction, delete_fraction;
pthread_mutex_t mutex1;
int count_m, count_i, count_d;
float m_member, m_insert, m_delete;
int thread_count = 0;

int Member(int value, struct Node* head){
    struct Node* curr = head;

    while (curr != NULL && curr->data < value){
        curr = curr->next;
    }
    if(curr == NULL || curr->data > value){
        return 0;
    }
    else{
        return 1;
    }
}

int Insert(int value, struct Node** head){
    struct Node* curr = *head;
    struct Node* pred = NULL;
    struct Node* temp;

    while (curr != NULL && curr->data < value){
        pred =  curr;
        curr = curr->next;
    }
    if(curr == NULL || curr->data > value){
        temp =  malloc(sizeof(struct Node));
        temp->data =  value;
        temp->next = curr;
        if(pred==NULL){
            *head = temp;
        }
        else{
            pred->next = temp;
        }
        return 1;
    }
    else{
        return 0;
    }


}

int Delete(int value, struct Node** head){
    struct Node* curr = *head;
    struct Node* pred = NULL;

    while (curr != NULL && curr->data < value){
        pred =  curr;
        curr = curr->next;
    }
    if(curr != NULL && curr->data == value){
        if(pred==NULL){
            *head = curr->next;
            free(curr);
        }
        else{
            pred->next = curr->next;
            free(curr);
        }
        return 1;
    }
    else{
        return 0;
    }


}

void *Thread(void* rank){

    int count = 0;
    int member_is_finished = 0;
    int insert_is_finished = 0;
    int delete_is_finished = 0;
    while(count<m){
        int random_value = rand() % 65535;
        int random_ops =  rand() % 3;
        if(random_ops == 0 && member_is_finished == 0){
            pthread_mutex_lock( &mutex1 );
            if(count_m < m_member){
                Member(random_value,head);
                count_m++;
            }
            else{
                member_is_finished = 1;
            }    
            pthread_mutex_unlock( &mutex1 ); 
        }
        if(random_ops == 1 && insert_is_finished == 0){
            pthread_mutex_lock( &mutex1 );
            if(count_i < m_insert){
                Insert(random_value,&head);
                count_i++;
            }
            else{
                insert_is_finished = 1;
            }    
            pthread_mutex_unlock( &mutex1 ); 
        }
        if(random_ops == 2 && delete_is_finished == 0){
            pthread_mutex_lock( &mutex1 );
            if(count_d < m_delete){
                Delete(random_value,&head);
                count_d++;
            }
            else{
                delete_is_finished = 1;
            }    
            pthread_mutex_unlock( &mutex1 ); 
        }
        count = count_m+count_i+count_d;
    }
    return NULL;

}

double GetTimeDiff(struct timeval time_begin, struct timeval time_end) {
    return (double) (time_end.tv_usec - time_begin.tv_usec) / 1000000 + (double) (time_end.tv_sec - time_begin.tv_sec);
}


int main(int argc, char* argv[])
{
    int lower = 1;
    int upper = pow(2,16);
    long thread;
    struct timeval start_time, end_time;
    double diff_time;
    pthread_t* thread_handles;

    thread_count = strtol(argv[1],NULL,10);
    n = (int) strtol(argv[2],NULL,10);
    m = (int) strtol(argv[3],NULL,10);

    member_fraction = (float) atof(argv[4]);
    insert_fraction = (float) atof(argv[5]);
    delete_fraction = (float) atof(argv[6]);

    m_member = m * member_fraction;
    m_insert = m * insert_fraction;
    m_delete = m * delete_fraction;

    int i = 0;
    while (i < n) {
        if (Insert(rand() % 65535, &head) == 1)
            i++;
    } 


    thread_handles =  malloc(thread_count*sizeof(pthread_t));
    pthread_mutex_init(&mutex1, NULL);

    gettimeofday(&start_time, NULL);
    
    for (thread = 0; thread < thread_count; thread++)
    {
    pthread_create(&thread_handles[thread], NULL, Thread, (void*) thread);
    }
    for (thread = 0; thread < thread_count; thread++)
    {
    pthread_join(thread_handles[thread], NULL);
    }
    
    gettimeofday(&end_time, NULL);

    pthread_mutex_destroy(&mutex1);
    printf("%f", GetTimeDiff(start_time, end_time));
    free(thread_handles);


    return 0;
}