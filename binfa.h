#include <SDL2/SDL.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>

#ifndef BINFA
    #define BINFA

#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1000
typedef struct fa{
    /** @brief A fa gyökere által tárolt adat*/
    int data;
    /** @brief A fa jobb ága*/
    struct fa *r;
    /** @brief A fa bal ága*/
    struct fa *l;
}fa;

void freefa(fa *root){
    if(root == NULL) return;
    freefa(root->l);
    freefa(root->r);
    free(root);
}

fa *beszur(fa *gyoker, int ertek) {
    if (gyoker == NULL) {
        fa *uj = (fa*) malloc(sizeof(fa));
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

void draw_circle(SDL_Renderer *renderer, int x, int y, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void fn_bifa_megjelenit(SDL_Renderer *renderer, TTF_Font* font, fa *node, int x, int y, int depth, int radius) {
    if (node == NULL) return;

    if (node->l) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, x, y, x - 176/(depth+1), y + 80);
        fn_bifa_megjelenit(renderer, font, node->l, x - 176/(depth+1), y + 80, depth + 1, radius);
    }
    if (node->r) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, x, y, x + 176/(depth+1), y + 80);
        fn_bifa_megjelenit(renderer, font, node->r, x + 176/(depth+1), y + 80, depth + 1, radius);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    draw_circle(renderer, x, y, radius);

    char value_str[12];
    sprintf(value_str, "%d", node->data);
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, value_str, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dstrect = {x-radius/2+1, y-radius/2+1, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void bifa_megjelenit(fa *node, int depth, int radius) {
    SDL_Init(SDL_INIT_VIDEO);

    if (TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }

    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/google-droid-sans-fonts/DroidSans.ttf", 20);
    if (font == NULL) printf("TTF_OpenFont: %s\n", TTF_GetError());

    SDL_Window *window = SDL_CreateWindow("Tree Display", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    fn_bifa_megjelenit(renderer, font, node, WINDOW_WIDTH/2, 50, depth, radius);

    SDL_RenderPresent(renderer);
    SDL_Event event;
    while (SDL_WaitEvent(&event) && event.type != SDL_QUIT && event.type != SDL_MOUSEBUTTONDOWN);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
}

#endif