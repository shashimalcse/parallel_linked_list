#include<stdio.h> // define the header file  
#include<stdlib.h>
#include<pthread.h>

struct Node {
    int data;
    struct Node* next;
};

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
    if(curr == NULL || curr->data > value){
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

struct Node* head = NULL;
int main()
{
    
    Insert(1,&head);
    Insert(2,&head);
    Insert(3,&head);

    printList(head);
 
    return 0;
}