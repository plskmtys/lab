#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"
#define COUNT 6

typedef struct node{
    int data;
    struct node *next;
}node;

typedef struct node2{
    int data;
    struct node2 *next;
    struct node2 *prev;
}node2;

typedef struct fa_i{
    int data;
    struct fa_i *r;
    struct fa_i *l;
}fa_i;

fa_i *beszur(fa_i *gyoker, int ertek) {
    if (gyoker == NULL) {
        fa_i *uj = (fa_i*) malloc(sizeof(fa_i));
        uj->data = ertek;
        uj->l = uj->r = NULL;
        return uj;
    }
    if (ertek < gyoker->data) {        /* balra szur */
        gyoker->l = beszur(gyoker->l, ertek);
    }
    else if (ertek > gyoker->data) {   /* jobbra szur */
        gyoker->r = beszur(gyoker->r, ertek);
    }
    else {
        /* mar benne van */
    }
    return gyoker;
}

void freelist(node* head){
    node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void freelist2(node2* head){
    node2* temp;
    while(head != NULL){
        temp = head;
        head = head->next;
        if(head != NULL) head->prev = NULL;
        free(temp);
    }
}

void freefa(fa_i *root){
    if(root == NULL) return;
    freefa(root->l);
    freefa(root->r);
    free(root);
}

int mikulas(fa_i *root){
    if(root == NULL) return 0;
    int sum = root->data;
    root->data = 0;

    sum += mikulas(root->l);
    sum += mikulas(root->r);

    if(root->l == NULL && root->r == NULL){
        root->data = sum;
    }
    return sum;
}

node *last(node *head){
    if(head == NULL) return NULL;
    node *iter;
    for(iter = head; iter->next != NULL; iter = iter->next);
    return iter;
}

node *elsokbol_utolsok(node *head){
    if(head == NULL || head->next == NULL) return NULL;
    node* l = last(head);
    node *newhead = head->next;
    l->next = head;
    head->next = NULL;
    return newhead;
}

node *utolsokbol_elsok(node *head){
    if(head == NULL || head->next == NULL) return NULL;
    node *iter;
    for(iter = head; iter->next->next != NULL; iter = iter->next);
    node *l = iter->next;
    head = l;
    iter->next = NULL;
    return head;
}

int szintsorszam(fa_i* root, int level){
    if(root == NULL) return 0;
    root->data = level;
    szintsorszam(root->l, level+1);
    szintsorszam(root->r, level+1);
    return level;
}


// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(fa_i* root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->r, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);
 
    // Process left child
    print2DUtil(root->l, space);
}

 
// Wrapper over print2DUtil()
void print2D(fa_i* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

int cseresznye(fa_i *root){
    if(root == NULL) return 0;
    if(root->l != NULL && root->r != NULL && root->l->l == NULL && root->l->r == NULL && root->r->l == NULL && root->r->r == NULL) return 1;
    return cseresznye(root->l) + cseresznye(root->r);
}

bool kukac(fa_i *root){
    if(root == NULL) return true;
    if(root->l != NULL && root->r != NULL) return false;
    if(kukac(root->l)) return true;
    return kukac(root->r);
}

bool keresofa(fa_i *root){
    if(root == NULL) return true;
    if(root->l == NULL && root->r == NULL) return true;
    if(root->r == NULL) return keresofa(root->l);
    if(root->l == NULL) return keresofa(root->r);
    if(root->l->data < root->data && root->r->data > root->data) return true;
    return keresofa(root->l) && keresofa(root->r);
}

void ordered_insert(node2** head, int adat){
    node2 *uj = (node2*) malloc(sizeof(node));
    uj->data = adat;
    if(*head == NULL){
        uj->prev = NULL;
        uj->next = NULL;
        *head = uj;
        return;
    }
    if(adat < (*head)->data){
        uj->prev = NULL;
        uj->next = *head;
        *head = uj;
        return;
    }
    node2 *iter = *head;
    for(iter = *head; iter->next != NULL && iter->next->data <= adat; iter = iter->next){

    }
    uj->next = iter->next;
    if(iter->next != NULL){
        iter->next->prev = uj;
    }
    uj->prev = iter;
    iter->next = uj;
    return;
}

int main(){
    printf("1.\nLista\n");
    node *eleje;
    eleje = (node*) malloc(sizeof(node));
    eleje->data = 3;
    eleje->next = (node*) malloc(sizeof(node));
    eleje->next->data = 4;
    eleje->next->next = NULL;
    //feladatok
    eleje = elsokbol_utolsok(eleje);
    freelist(eleje);


    node2 *eleje2 = (node2*) malloc(sizeof(node2));
    printf("2.\nFa\n");
    int minta[] = {4, 6, 15, 96, 34, 12, 14, 56, 21, 11, 0};
    //későbbi feladatok ellenőrzéséhez
    size_t tombelemszam = 0;
    int tombosszeg = 0;

    for(int i=0; minta[i] != 0; i++){
        ordered_insert(&eleje2, minta[i]);
    }

    for(int i =0; minta[i] != 0; i++){
        printf("%d ",eleje2->data);
        eleje2 = eleje2->next;
    }



    fa_i *gyoker = NULL;
    for (int i = 0; minta[i] > 0; i++){
        gyoker = beszur(gyoker, minta[i]);
        tombelemszam++;
        tombosszeg+=minta[i];
    }
    printf("\nellenőrzéshez:\ntömb elemszám: %lu\ntömbösszeg: %d\n", tombelemszam, tombosszeg);
    //feladatok

    int osszeg = mikulas(gyoker);
    printf("faosszeg: %d\n", osszeg);

    //print2D(gyoker);

    szintsorszam(gyoker, 0);
    //print2D(gyoker);

    int cs = cseresznye(gyoker);
    printf("cseresznyek szama: %d\n", cs);

    kukac(gyoker) ? printf("kukac\n") : printf("nem kukac\n");
    keresofa(gyoker) ? printf("keresofa\n") : printf("nem keresofa\n");

    freefa(gyoker);
    freelist2(eleje2);
}