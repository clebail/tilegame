//----------------------------------------------------------------------------
#ifndef __CWIDGETSIMULATESDL_H__
#define __CWIDGETSIMULATESDL_H__
//----------------------------------------------------------------------------
#include <SDL.h>
//----------------------------------------------------------------------------
class CWidgetSimulateSDL {
public:
    explicit CWidgetSimulateSDL(void);
    ~CWidgetSimulateSDL(void);
    void exec(void);
private:
    SDL_Window *window;
};
//----------------------------------------------------------------------------
#endif // __CWIDGETSIMULATESDL_H__
//----------------------------------------------------------------------------
