#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *sor_beolvas(){
    size_t maxlen = 10;
    char *new = (char*) malloc(sizeof(char)*maxlen);
    size_t len = 0;
    int c = getchar();
    while(c != '\n' && c != EOF){
        len++;
        if(len == maxlen){
            maxlen += 10;
            char *longer = (char*) malloc(sizeof(char)*maxlen);
            strncpy(longer, new, len);
        }
        new[len-1] = c;
        new[len] = '\0';
        c = getchar();
    }
    return new;
}

char* spacex(char *input, char swap, size_t db){
    size_t size;
    for(size = 0; input[size] != '\0'; size++);
    size_t newsize = size + 1 + 2*db;
    char *output = (char*) malloc(sizeof(char)*(newsize));
    size_t j = 0;
    for(size_t i = 0; i<newsize; i++){
        if(i<db || i >= size+db){
            output[i] = swap;
        } else if (input[j] == ' '){
            output[i] = swap;
            j++;
        } else {
            output[i] = input[j];
            j++;
        }
    }
    output[newsize-1] = '\0';
    return output;
}

int strcmp_the(char* a, char* b){
    if(strncmp("The ", a, 4) == 0){
        a += 4;
    } else if (strncmp("The ", b, 4) == 0){
        b += 4;
    }
    return strcmp(a, b);
}

u_int32_t ipv4addr(const char* address_str){
    u_int32_t part1 = 0, part2 = 0, part3 = 0, part4 = 0;
    sscanf(address_str, "%u.%u.%u.%u", &part1, &part2, &part3, &part4);
    return part1<<24 | part2<<16 | part3<<8 | part4;
}

int main(){
    printf("adj meg egy tetszolegesen hosszu szoveget!\n");

    char *input = sor_beolvas();

    printf("beolvasott sztring: %s\n", input);
    printf("kicserélt sztring: %s\n", spacex("Hello hallo elektor kalandor", 'x', 3));
    printf("%u\n", ipv4addr("192.168.0.1"));
    printf("%c%c%c%c%c%c%c%c%c%c%c\n", 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x4E, 0x69, 0x67, 0x67, 0x61);
}