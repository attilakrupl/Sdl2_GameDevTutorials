#pragma once

#include <SDL.h>
#include <stdio.h>

class drkrWindow
{
public:
    drkrWindow();
    ~drkrWindow();

    bool init();
    bool loadMedia();
    void close();

private:
    SDL_Window*  m_pWindow        = nullptr;
    SDL_Surface* m_pScreenSurface = nullptr;
    SDL_Surface* m_pXOut          = nullptr;
};
