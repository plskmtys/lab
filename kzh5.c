#include <stdio.h>
#include <string.h>
#include "debugmalloc.h"
#include <stdbool.h>

bool contains(const char needle, const char *haystack){
    for(int i=0; haystack[i] != '\0'; i++) if(haystack[i] == needle) return true;
    return false;
}

char *dynamic_squeeze(char *text, char *except){
    size_t textlen = strlen(text);
    size_t newlen = 0;
    for(int i=0; i<textlen+1; i++) if(!contains(text[i], except)) newlen++;
    char *uj = (char*) malloc(sizeof(char)*(newlen+1));
    size_t uj_i = 0;
    for(size_t i = 0UL; i < textlen+1; i++){
        if(!contains(text[i], except)){
            uj[uj_i]=text[i];
            uj_i++;
        }
    }
    uj[uj_i] = '\0';
    return uj;
}

int main(){
    char *uj = dynamic_squeeze("almale", "aeoiu");
    printf("\n%s\n", uj);
    free(uj);
}