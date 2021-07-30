#include<stdio.h> // define the header file  
#include<stdlib.h>
#include<pthread.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>


// Linked List Node
struct Node {
    int data;
    struct Node* next;
};

//Global variables

struct Node* head = NULL;
int n;
int m;
float member_fraction, insert_fraction, delete_fraction;
int count, count_m, count_i, count_d;
float m_member, m_insert, m_delete;

//Member function

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

//Inser function

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

//Delete function

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

//Time differnce function

double GetTimeDiff(struct timeval time_begin, struct timeval time_end) {
    return (double) (time_end.tv_usec - time_begin.tv_usec) / 1000000 + (double) (time_end.tv_sec - time_begin.tv_sec);
}

int main(int argc, char* argv[])
{

    struct timeval start_time, end_time;
    double diff_time;

    n = (int) strtol(argv[1],NULL,10);
    m = (int) strtol(argv[2],NULL,10);

    member_fraction = (float) atof(argv[3]);
    insert_fraction = (float) atof(argv[4]);
    delete_fraction = (float) atof(argv[5]);

    m_member = m * member_fraction;
    m_insert = m * insert_fraction;
    m_delete = m * delete_fraction;

    int i = 0;
    while (i < n) {
        if (Insert(rand() % 65535, &head) == 1)
            i++;
    } 

    gettimeofday(&start_time, NULL);
    
    while(count<m){
        int random_value = rand() % 65535;
        if(count_m < m_member){
            Member(random_value,head);
            count_m++;
        }
        else if(count_i < m_insert){
            Insert(random_value,&head);
            count_i++;
        }
        else{
            Delete(random_value,&head);
            count_d++;
        }
        count =  count_m+count_i+count_d;
    }
    
    gettimeofday(&end_time, NULL);
    printf("%f", GetTimeDiff(start_time, end_time));
    return 0;
}
