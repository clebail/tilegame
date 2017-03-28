//----------------------------------------------------------------------------
#include <QtDebug>
#include <common.h>
#include "CWidgetSimulateSDL.h"
//----------------------------------------------------------------------------
CWidgetSimulateSDL::CWidgetSimulateSDL(void) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Simule",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GAME_WIDTH, GAME_HEIGHT, SDL_WINDOW_SHOWN);
}
//----------------------------------------------------------------------------
CWidgetSimulateSDL::~CWidgetSimulateSDL(void) {
    if(window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}
//----------------------------------------------------------------------------
void CWidgetSimulateSDL::exec(void) {
    bool finish = false;
    SDL_Event event;

    while(!finish) {
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_CLOSE) {
                    finish = true;
                }
                break;
            default:
                break;
            }
        }
    }
}
//----------------------------------------------------------------------------
