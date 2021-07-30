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
pthread_mutex_t mutex1;
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
long my_rank = (long) rank;
    double factor, my_sum = 0.0;
    long long i;
    int val;
    long long my_m = m/thread_count;

	for (i = 0; i < my_m; i++) {
		float operation_choice = (rand()%10000/10000.0);
		val = rand()%65535;
	  
		if (operation_choice < m_member) {
			pthread_rwlock_rdlock(&rwlock);
			Member(val,head);
            count_m++;
			pthread_rwlock_unlock(&rwlock);
		} else if (operation_choice < m_member + m_insert) {
			pthread_rwlock_wrlock(&rwlock);
			Insert(val,&head);
            count_i++;
			pthread_rwlock_unlock(&rwlock);
			
		} else {
			pthread_rwlock_wrlock(&rwlock);
			Delete(val,&head);
            count_d++;
			pthread_rwlock_unlock(&rwlock);	
		}
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
    pthread_mutex_init(&mutex1, NULL);
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
    pthread_mutex_destroy(&mutex1);
    pthread_rwlock_destroy(&rwlock);
    diff_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("%f", diff_time);
    printf("%f", diff_time);
    free(thread_handles);

    return 0;
}
