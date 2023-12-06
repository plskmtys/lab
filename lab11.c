#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"
 
typedef struct BiFa {
    int ertek;
    struct BiFa *bal, *jobb;
} BiFa;
 
BiFa *beszur(BiFa *gyoker, int ertek) {
    if (gyoker == NULL) {
        BiFa *uj = (BiFa*) malloc(sizeof(BiFa));
        uj->ertek = ertek;
        uj->bal = uj->jobb = NULL;
        return uj;
    }
    if (ertek < gyoker->ertek) {        /* balra szur */
        gyoker->bal = beszur(gyoker->bal, ertek);
    }
    else if (ertek > gyoker->ertek) {   /* jobbra szur */
        gyoker->jobb = beszur(gyoker->jobb, ertek);
    }
    else {
        /* mar benne van */
    }
    return gyoker;
}

void bifa_bejar_inorder(BiFa *gyoker){
    if(gyoker == NULL) return;
    bifa_bejar_inorder(gyoker->bal);
    printf("%d\n", gyoker->ertek);
    bifa_bejar_inorder(gyoker->jobb);
}

void bifa_free(BiFa *gyoker){
    if(gyoker == NULL) return;
    bifa_free(gyoker->bal);
    bifa_free(gyoker->jobb);
    free(gyoker);
}

size_t bifa_count(BiFa *gyoker){
    if(gyoker == NULL) return 0;
    return bifa_count(gyoker->bal)+bifa_count(gyoker->jobb)+1;
}

int bifa_sum(BiFa *gyoker){
    if(gyoker == NULL) return 0;
    return bifa_sum(gyoker->bal)+bifa_sum(gyoker->jobb)+gyoker->ertek;
}

BiFa *bifa_search(BiFa *gyoker, int needle){
    if(gyoker == NULL) return NULL;
    if(gyoker->ertek == needle) return gyoker;
    if(gyoker->ertek < needle) return bifa_search(gyoker->jobb, needle);
    else return bifa_search(gyoker->bal, needle);
}

BiFa *bifa_negalt_search(BiFa *gyoker, int needle){
    if(gyoker == NULL) return NULL;
    if(gyoker->ertek == needle) return gyoker;
    if(gyoker->ertek > needle) return bifa_search(gyoker->jobb, needle);
    else return bifa_search(gyoker->bal, needle);
}

void bifa_negalt(BiFa *gyoker){
    if(gyoker == NULL) return;
    bifa_negalt(gyoker->bal);
    bifa_negalt(gyoker->jobb);
    gyoker->ertek *= -1;
}

void bifa_tukroz(BiFa *gyoker){
    if(gyoker == NULL) return;
    bifa_tukroz(gyoker->bal);
    bifa_tukroz(gyoker->jobb);
    BiFa *temp = gyoker->bal;
    gyoker->bal = gyoker->jobb;
    gyoker->jobb = temp;
}

int main(void) {
    int minta[] = {15, 96, 34, 12, 14, 56, 21, 11, 10, 9, 78, 43, 0};

    //későbbi feladatok ellenőrzéséhez:
    size_t tombelemszam = 0;
    int tombosszeg = 0;

    BiFa *gyoker = NULL;
    for (int i = 0; minta[i] > 0; i++){
        gyoker = beszur(gyoker, minta[i]);
        tombelemszam++;
        tombosszeg+=minta[i];
    }
    /* Ide tedd be a kipróbálandó függvények hívásait! */
    printf("3.\n");
    bifa_bejar_inorder(gyoker);

    printf("4.\n");
    size_t cnt = bifa_count(gyoker);
    printf("darabszám: %d, ", cnt);
    printf(tombelemszam==cnt ? "helyes eredmény\n" : "hibás eredmény\n");

    int sum = bifa_sum(gyoker);
    printf("összeg: %d, ", sum);
    printf(tombosszeg==sum ? "helyes eredmény\n" : "hibás eredmény\n");
    
    printf("5.\n");
    BiFa *found = bifa_search(gyoker, 21);
    printf(found != NULL ? "megtaláltam: %d\n" : "nem találtam meg\n", found->ertek);

    printf("6.\n");
    bifa_negalt(gyoker);
    BiFa *found2 = bifa_negalt_search(gyoker, -21);
    printf(found != NULL ? "megtaláltam: %d\n" : "nem találtam meg\n", found->ertek);

    printf("7.\n");
    bifa_tukroz(gyoker);
    BiFa *found3 = bifa_negalt_search(gyoker, -21);
    printf(found != NULL ? "megtaláltam: %d\n" : "nem találtam meg\n", found->ertek);

    bifa_free(gyoker);
    return 0;
}
