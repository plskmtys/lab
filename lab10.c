#include <stdlib.h>
#include <stdio.h>
#include "debugmalloc.h"
#include <stdbool.h>
 
typedef struct ListaElem {
    int adat;
    struct ListaElem *kov;
} ListaElem;

ListaElem *lista_letrehoz(void) {
    int szamok[] = { 8, 14, 13, 17, 1, 19, 16, 5, 3, 11, 2,
                     15, 9, 10, 6, 22, 4, 7, 18, 27, -1 };
    ListaElem *lis = NULL;
 
    for (int i = 0; szamok[i] != -1; ++i) {
        ListaElem *u;
        u = (ListaElem*) malloc(sizeof(ListaElem));
        u->kov = lis;
        u->adat = szamok[i];
        lis = u;
    }
    return lis;
}

int listahossz(ListaElem *elso){
    ListaElem *eleje = elso;
    int hossz=0;
    for (ListaElem *current = eleje; current != NULL; current=current->kov) hossz++;
    return hossz;
}

void lista_free(ListaElem *eleje){
    ListaElem *iter = eleje;
    while (iter != NULL) {
        ListaElem *kov = iter->kov;
        free(iter);
        iter = kov;
    }
}

ListaElem *elore_beszur(ListaElem *eleje, int adat) {
   ListaElem *uj;
   uj = (ListaElem*) malloc(sizeof(ListaElem));
   uj->adat = adat;
   uj->kov = eleje;
   return uj;
}

ListaElem *GetLastItem(ListaElem *eleje){
    ListaElem *last;
    for (last = eleje; ; last=last->kov)
    {
        if(last->kov  == NULL) return last; 
    }
    return NULL;
}

ListaElem *vegere_beszur(ListaElem *eleje, int adat){
    ListaElem *uj;
    uj = (ListaElem*) malloc(sizeof(ListaElem));
    uj->adat = adat;
    uj->kov = NULL;
    if (eleje == NULL) {
        eleje = uj;
        //vege = uj;
    } else {
        ListaElem *vege = GetLastItem(eleje);
        vege->kov = uj;
        vege = uj;
    }
    return eleje;
}

ListaElem *keres(ListaElem *eleje, int keresett){
    ListaElem *iter;
    for (iter = eleje; iter != NULL; iter=iter->kov)
        if(iter->adat==keresett) return iter;
    return NULL;
}
 
 
int main() {
    ListaElem *eleje;
    eleje = lista_letrehoz();
    eleje = elore_beszur(eleje, 69);
    ListaElem *vege;
    vege = GetLastItem(eleje);
    vege = vegere_beszur(eleje, 420);
    for (ListaElem *current = eleje; current != NULL; current=current->kov)
        printf("%d ", current->adat);
    int i=0, i2=0;
    for (ListaElem *current = eleje; current != NULL; current=current->kov)
        i++;
    i2=listahossz(eleje);
    printf("\n%d db elem van a listában\nFügvénnyel: %d db\n", i, i2);
    ListaElem *keresett = keres(eleje, 420);
    keresett!=NULL ? printf("megtaláltam, %d\n", keresett->adat) : printf("nem találtam meg\n");
    lista_free(eleje);
}