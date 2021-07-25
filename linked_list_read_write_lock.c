#include <stdio.h> // define the header file
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

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
int count_m, count_i, count_d;
float m_member, m_insert, m_delete;
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

    int count = 0;
    while (count < m)
    {
        int random_value = rand() % 65535;
        if (count_m < m_member)
        {
            /* Read lock */
            pthread_rwlock_rdlock(&rwlock);
            Member(random_value, head);
            count_m++;
            pthread_rwlock_unlock(&rwlock);
        }
        else if (count_i < m_insert)
        {
            /* Write lock */
            pthread_rwlock_wrlock(&rwlock);
            Insert(random_value, &head);
            count_i++;
            pthread_rwlock_unlock(&rwlock);
        }
        else
        {
            /* Write lock */
            pthread_rwlock_wrlock(&rwlock);
            Delete(random_value, &head);
            count_d++;
            pthread_rwlock_unlock(&rwlock);
        }
        count = count_m + count_i + count_d;
    }
    return NULL;
}

int main(int argc, char* argv[]){

    long thread;
    clock_t start_time, end_time;
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

    start_time = clock();

    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_create(&thread_handles[thread], NULL, Thread, (void *)thread);
    }
    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_join(thread_handles[thread], NULL);
    }

    end_time = clock();

    pthread_rwlock_destroy(&rwlock);
    diff_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("%f", diff_time);
    free(thread_handles);

    return 0;
}