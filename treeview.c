#include <SDL2/SDL.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>
#include "binfa.h"

int main() {

    int minta[] = {15, 96, 34, 12, 14, 56, 21, 11, 20, 25, 76, 1, 5, 13, 15, 16, 17, 55, 110, 100, 99, 0};
    fa *gyoker = NULL;
    for (int i = 0; minta[i] > 0; i++){
        gyoker = beszur(gyoker, minta[i]);
    }

    bifa_megjelenit(gyoker, 0, 24);

    freefa(gyoker);

    return 0;
}