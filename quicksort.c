#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef bool
    #include <stdbool.h>
#endif

typedef struct Node{
    int data;
    struct Node *next;
}Node;

void FreeList(Node* head){
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

Node *InsertToEnd(Node* head, int data){
    Node* new = (Node*) malloc(sizeof(Node));
    new->data = data;
    new->next = NULL;
    if(head == NULL){
        head = new;
        return head;
    }
    Node *iter;
    for(iter = head; iter->next != NULL; iter = iter->next);
    iter->next = new;
    return head;
}

void InsertAfter(Node **chosen, int data){
    Node *new = (Node*) malloc(sizeof(Node));
    new->data = data;
    if(*chosen == NULL){
        *chosen = new;
        (*chosen)->next = NULL;
    }
    
    if((*chosen)->next == NULL){
        (*chosen)->next = new;
        new->next = NULL;
    }
}

Node *BuildList(int arr[], size_t size){
    Node *head = (Node*) malloc(sizeof(Node));
    head->data = arr[0];
    for(size_t i=1; i < size; i++){
        head = InsertToEnd(head, arr[i]);
    }
    return head;
}

void PrintList(Node *head){
    if(head == NULL){
        printf("üres lista\n");
    }

    Node* iter;
    for(iter = head; iter->next != NULL; iter = iter->next){
        printf("%d, ", iter->data);
    }
    printf("%d\n", iter->data);
    return;
}
/*
void Merge(Node *left, Node *right){

}

Node *MergeSort(Node* head){

}
*/

int cmp(void const *a, void const *b){
    int const *sz1 = (int const *)a;
    int const *sz2 = (int const *)b;
    if(*sz1 == *sz2) return 0;
    if(*sz1 > *sz2) return 1;
    return -1;
}

int LinearisKereses(int haystack[], int needle, int size, bool reverse){
    if(haystack == NULL) return -1;
    int nov = 1;
    int start = 0;
    int end = size;
    
    if(reverse){
        nov = -1;
        start = size-1;
        end = -1;
    }
    
    for(int i = start; i != end; i+=nov){
        if(needle == haystack[i]){
            return i;
        }
    }
    return -1;
}

int BinarisKereses(int const haystack[], int const needle, int low, int high){
    if(high>=low){
        int mid = low + (high-low) / 2;

        if(haystack[mid] == needle){
            return mid;

        }

        return (haystack[mid] < needle ? BinarisKereses(haystack, needle, mid+1, high) : BinarisKereses(haystack, needle, low, mid-1));
    }
    return -1;
}

int main(){
    int tomb[] = {32, 7, 11, 4, 3, 7, 9, 15, 66, 44, 51, 21, 19, 37};
    
    Node *head = BuildList(tomb, 14);
    head = InsertToEnd(head, 69);
    printf("unsorted list:\n");
    PrintList(head);

    qsort(tomb, 14, sizeof(int), cmp);
    printf("sorted list:\n");
    for(int i = 0; i< 14; i++) printf("%d, ", tomb[i]); 
    printf("\n");

    int rtomb[50];
    time_t t;
    srand((unsigned) time(&t));
    for(int i = 0; i<50; i++){
        rtomb[i] = rand() % 50;
    }

    qsort(rtomb, 50, sizeof(int), cmp);
    int first = LinearisKereses(rtomb, 23, 50, false);
    int last = LinearisKereses(rtomb, 23, 50, true);

    printf("eleje: %d\nvege: %d\n", first, last);

    first = BinarisKereses(rtomb, 23, 0, 50);
    last = BinarisKereses(rtomb, 23, 0, 50);
    printf("eleje: %d\nvege: %d\n", first, last);

    //free
    FreeList(head);
}