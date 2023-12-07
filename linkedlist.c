#include <stdio.h>
#include <stdlib.h>

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

void torol(Node **prev){
    if(*prev == NULL) return;
    Node *temp = (*prev)->next;
    (*prev)->next = temp->next;
    free(temp);
    return;
}

void torol_nth(Node **head, size_t n){
    if(*head == NULL) return;
    Node *mozgo = *head;
    Node *lemarado = NULL;
    size_t i = 0;
    while(mozgo != NULL && i != n){
        lemarado = mozgo;
        mozgo = mozgo->next;
        i++;
    }

    if(mozgo == NULL){
        //nincs ennyi elem a listában, kiléphetünk
        return;
    } else if(lemarado == NULL){
        //elso elem torlese
        Node *tmp = mozgo->next;
        free(mozgo);
        **head = *tmp;
        return;
    } else {
        lemarado->next = mozgo->next;
        free(mozgo);
        return;
    }
}

void paros_torol(Node **head){
    if(*head == NULL) return;
    size_t i = 1;
    Node *mozgo = *head;
    Node *lemarado = NULL;
    while(mozgo != NULL){
        if(i%2 == 0){
            lemarado->next = mozgo->next;
            Node *tmp = mozgo;
            lemarado = mozgo;
            mozgo = mozgo->next;
            free(tmp);
            i++;
        } else {
            lemarado = mozgo;
            mozgo = mozgo->next;
            i++;
        }
    }
}

int main(){
    int tomb[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Node *head = BuildList(tomb, sizeof(tomb)/sizeof(int));
    printf("eredeti lista:\n");
    PrintList(head);
    //torol(&head->next);
    torol_nth(&head, 5);
    printf("torolt harmadik elem:\n");
    PrintList(head);
    printf("paros indexuek torlese:\n");
    paros_torol(&head);
    PrintList(head);
}