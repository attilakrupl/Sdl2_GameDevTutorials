#pragma once

#include <SDL.h>

#include <stdio.h>
#include <string>

#include "h/common.h"

class drkrWindow
{
public:
    drkrWindow();
    ~drkrWindow();

    bool init();
    bool loadMedia();
    void close();
    SDL_Surface* loadSurface( std::string aPath );

    void setCurrentSurface( SDL_Surface* aSurface );
    SDL_Surface* getCurrentSurface();
    SDL_Surface* getSurface( DRKR::KeyPressSurfaces aSurfaceEnum );

    bool updateWindow();

private:
    SDL_Window*  m_pWindow         = nullptr;
    SDL_Surface* m_pScreenSurface  = nullptr;
    SDL_Surface* m_pCurrentSurface = nullptr;
    SDL_Surface* m_pKeyPressSurfaces[ DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_TOTAL ];
};