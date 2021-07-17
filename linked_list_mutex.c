#include<stdio.h> // define the header file  
#include<stdlib.h>
#include<pthread.h>
#include <math.h>
#include <time.h>



struct Node {
    int data;
    struct Node* next;
};

struct Node* head = NULL;
int n;
int m;
float member_fraction, insert_fraction, delete_fraction;
pthread_mutex_t mutex1,mutex2;
int count, count_m, count_i, count_d;
float m_member, m_insert, m_delete;
int thread_count = 0;
int* opr_data; 
int* link_data; 

void printList(struct Node* n)
{
    while (n != NULL) {
        printf(" %d ", n->data);
        n = n->next;
    }
}

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

int RandomGenerator(int *data,int count){
    int lower = 1;
    int upper = pow(2,16);
    for (int i = 0; i < count; i++) {
        int num = (rand() % (upper - lower + 1)) + lower;
        data[i] = num;
        for ( int j = 0; j <= i-1; j++ ) {
            if ( data[j] == data[i] )
            i--;
            }
    }



    return 0;
}

void *Thread(void* rank){
    while(count<m){
        if(count_m < sizeof(m_member)){
            pthread_mutex_lock( &mutex1 );    
            Member(opr_data[count],head);
            count_m++;
            pthread_mutex_unlock( &mutex1 ); 

        }
        else if(count_i < sizeof(m_insert) + sizeof(m_member)){
            pthread_mutex_lock( &mutex1 ); 
            Insert(opr_data[count],&head);
            count_i++;
            pthread_mutex_unlock( &mutex1 ); 
        }
        else{
            pthread_mutex_lock( &mutex1 ); 
            Delete(opr_data[count],&head);
            count_d++;
            pthread_mutex_unlock( &mutex1 ); 
        }
        pthread_mutex_lock( &mutex2 ); 
        count++;
        pthread_mutex_unlock( &mutex2 ); 
    }
    return NULL;

}


int main(int argc, char* argv[])
{
    int lower = 1;
    int upper = pow(2,16);
    long thread;
    int i;
    clock_t start_time, end_time;
    double diff_time;
    pthread_t* thread_handles;

    thread_count = strtol(argv[1],NULL,10);
    n = (int) strtol(argv[2],NULL,10);
    m = (int) strtol(argv[3],NULL,10);

    member_fraction = (float) atof(argv[4]);
    insert_fraction = (float) atof(argv[5]);
    delete_fraction = (float) atof(argv[6]);

    printf("debug1 \n");

    opr_data =  malloc(m*sizeof(int));
    link_data = malloc(n*sizeof(int));
    m_member = m * member_fraction;
    m_insert = m * insert_fraction;
    m_delete = m * delete_fraction;

    printf("debug2 \n");

    RandomGenerator(opr_data,m);
    RandomGenerator(link_data,n);

    printf("debug3 \n");

    for (int i = 0; i < n; i++) {
        Insert(link_data[i],&head);
    } 

    printf("debug4 \n");

    thread_handles =  malloc(thread_count*sizeof(pthread_t));
    i = 0;
    pthread_mutex_init(&mutex1, NULL);
	pthread_mutex_init(&mutex2, NULL);
    printf("debug5 \n");

    start_time = clock();
    
    printf("debug6 \n");
    
    for (thread = 0; thread < thread_count; thread++)
    {
    pthread_create(&thread_handles[thread], NULL, Thread, (void*) thread);
    }
    for (thread = 0; thread < thread_count; thread++)
    {
    pthread_join(thread_handles[thread], NULL);
    }
    printf("debug7 \n");
    
    end_time =  clock();

    diff_time = ((double) (end_time-start_time))/ CLOCKS_PER_SEC;

    printf("%f",diff_time);
    free(thread_handles);


    return 0;
}