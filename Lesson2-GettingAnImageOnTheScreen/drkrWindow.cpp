#include "drkrWindow.h"

#include <SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


drkrWindow::drkrWindow()
{
}


drkrWindow::~drkrWindow()
{
}

bool drkrWindow::init()
{
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }

    m_pWindow = SDL_CreateWindow( "SDL Tutorial"
                                , SDL_WINDOWPOS_UNDEFINED
                                , SDL_WINDOWPOS_UNDEFINED
                                , SCREEN_WIDTH
                                , SCREEN_HEIGHT
                                , SDL_WINDOW_SHOWN );

    if( m_pWindow == nullptr )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }

    m_pScreenSurface = SDL_GetWindowSurface( m_pWindow );

    return true;
}

bool drkrWindow::loadMedia()
{
    bool lSuccess = true;

    m_pHelloWorld = SDL_LoadBMP( "../../resources/hello_world.bmp" );
    if( m_pHelloWorld == nullptr )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "../../resources/hello_world.bmp", SDL_GetError() );
        lSuccess = false;
    }

    SDL_BlitSurface( m_pHelloWorld, NULL, m_pScreenSurface, NULL );

    SDL_UpdateWindowSurface( m_pWindow );

    return lSuccess;
}

void drkrWindow::close()
{
    SDL_FreeSurface( m_pHelloWorld );
    m_pHelloWorld = nullptr;

    SDL_DestroyWindow( m_pWindow );
    m_pWindow = nullptr;

    SDL_Quit();
}
