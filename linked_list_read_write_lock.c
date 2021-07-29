#include <stdio.h> // define the header file
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *head = NULL;
int n;
int m;
float member_fraction, insert_fraction, delete_fraction;
pthread_rwlock_t rwlock;
pthread_mutex_t mutex1;
int m_member = 0, m_insert = 0, m_delete = 0;
int thread_count = 0;

int Member(int value, struct Node *head)
{
    struct Node *curr = head;

    while (curr != NULL && curr->data < value)
    {
        curr = curr->next;
    }
    if (curr == NULL || curr->data > value)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int Insert(int value, struct Node **head)
{
    struct Node *curr = *head;
    struct Node *pred = NULL;
    struct Node *temp;

    while (curr != NULL && curr->data < value)
    {
        pred = curr;
        curr = curr->next;
    }
    if (curr == NULL || curr->data > value)
    {
        temp = malloc(sizeof(struct Node));
        temp->data = value;
        temp->next = curr;
        if (pred == NULL)
        {
            *head = temp;
        }
        else
        {
            pred->next = temp;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

int Delete(int value, struct Node **head)
{
    struct Node *curr = *head;
    struct Node *pred = NULL;

    while (curr != NULL && curr->data < value)
    {
        pred = curr;
        curr = curr->next;
    }
    if (curr != NULL && curr->data == value)
    {
        if (pred == NULL)
        {
            *head = curr->next;
            free(curr);
        }
        else
        {
            pred->next = curr->next;
            free(curr);
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

void *Thread(void *rank)
{
    int id = (long) rank;

    int thread_m_member = 0;
    int thread_m_insert = 0;
    int thread_m_delete = 0;
    int thread_m = 0;
    if (m_member % thread_count == 0 || m_member % thread_count <= id) {
        thread_m_member = m_member / thread_count;
    }
    else if (m_member % thread_count > id) {
        thread_m_member = m_member / thread_count + 1;
    }
    if (m_insert % thread_count == 0 || m_insert % thread_count <= id) {
        thread_m_insert = m_insert / thread_count;
    }
    else if (m_insert % thread_count > id) {
        thread_m_insert = m_insert / thread_count + 1;
    }
    if (m_delete % thread_count == 0 || m_delete % thread_count <= id) {
        thread_m_delete = m_delete / thread_count;
    }
    else if (m_delete % thread_count > id) {
        thread_m_delete = m_delete / thread_count + 1;
    }

    thread_m = thread_m_delete + thread_m_insert + thread_m_member;

    int count = 0;
    int count_m=0; 
    int count_i=0;
    int count_d=0;

    int member_is_finished = 0;
    int insert_is_finished = 0;
    int delete_is_finished = 0;

    int i = 0;
    while(count<thread_m){
        int random_value = rand() % 65535;
        int random_ops =  rand() % 3;
        if(random_ops == 0 && member_is_finished == 0){
            
            if(count_m < thread_m_member){
                pthread_rwlock_rdlock( &rwlock );
                Member(random_value,head);
                pthread_rwlock_unlock( &rwlock ); 
                count_m++;
            }
            else{
                member_is_finished = 1;
            }    
            
        }
        else if(random_ops == 1 && insert_is_finished == 0){
            
            if(count_i < thread_m_insert){
                pthread_rwlock_wrlock( &rwlock );
                Insert(random_value,&head);
                pthread_rwlock_unlock( &rwlock ); 
                count_i++;
            }
            else{
                insert_is_finished = 1;
            }    
            
        }
        else if(random_ops == 2 && delete_is_finished == 0){
            
            if(count_d < thread_m_delete){
                pthread_rwlock_wrlock( &rwlock );
                Delete(random_value,&head);
                pthread_rwlock_unlock( &rwlock ); 
                count_d++;
            }
            else{
                delete_is_finished = 1;
            }    
            
        }
        count = count_m + count_i + count_d;
        i++;
        
    }
	return NULL;
}

double GetTimeDiff(struct timeval time_begin, struct timeval time_end) {
    return (double) (time_end.tv_usec - time_begin.tv_usec) / 1000000 + (double) (time_end.tv_sec - time_begin.tv_sec);
}

int main(int argc, char* argv[]){
    long thread;
    struct timeval start_time, end_time;
    double diff_time;
    pthread_t *thread_handles;

    thread_count = strtol(argv[1], NULL, 10);
    n = (int)strtol(argv[2], NULL, 10);
    m = (int)strtol(argv[3], NULL, 10);

    member_fraction = (float)atof(argv[4]);
    insert_fraction = (float)atof(argv[5]);
    delete_fraction = (float)atof(argv[6]);

    m_member = m * member_fraction;
    m_insert = m * insert_fraction;
    m_delete = m * delete_fraction;

    int i = 0;
    while (i < n)
    {
        if (Insert(rand() % 65535, &head) == 1)
            i++;
    }

    thread_handles = malloc(thread_count * sizeof(pthread_t));
    pthread_rwlock_init(&rwlock, NULL);

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
    pthread_rwlock_destroy(&rwlock);
    printf("%f", GetTimeDiff(start_time, end_time));
    free(thread_handles);
    return 0;
}