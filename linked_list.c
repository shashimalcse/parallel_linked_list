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
int count, count_m, count_i, count_d;
float m_member, m_insert, m_delete;

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



int main(int argc, char* argv[])
{

    clock_t start_time, end_time;
    double diff_time;

    n = (int) strtol(argv[1],NULL,10);
    m = (int) strtol(argv[2],NULL,10);

    member_fraction = (float) atof(argv[3]);
    insert_fraction = (float) atof(argv[4]);
    delete_fraction = (float) atof(argv[5]);

    m_member = m * member_fraction;
    m_insert = m * insert_fraction;
    m_delete = m * delete_fraction;

    // printf("%f %f %f \n", m_member, m_insert, m_delete);

    int i = 0;
    while (i < n) {
        if (Insert(rand() % 65535, &head) == 1)
            i++;
    } 

    start_time = clock();
    
    
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
    
    end_time =  clock();

    diff_time = ((double) (end_time-start_time))/ CLOCKS_PER_SEC;

    printf("%f",diff_time);

    return 0;
}