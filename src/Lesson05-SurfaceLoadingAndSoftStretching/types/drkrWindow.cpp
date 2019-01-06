#include "drkrWindow.h"
#include "h/macros.h"
#include "h/consts.h"

#include <SDL.h>

drkrWindow::drkrWindow()
{}

drkrWindow::~drkrWindow()
{}

bool drkrWindow::init()
{
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        PRINT_ERROR( SDL_GetError() );
        return false;
    }

    m_pWindow = SDL_CreateWindow( "SDL Tutorial"
        , SDL_WINDOWPOS_UNDEFINED
        , SDL_WINDOWPOS_UNDEFINED
        , 0
        , 0
        , SDL_WINDOW_FULLSCREEN );

    if( m_pWindow == nullptr )
    {
        PRINT_ERROR( SDL_GetError() );
        return false;
    }

    m_pScreenSurface = SDL_GetWindowSurface( m_pWindow );

    return true;
}

bool drkrWindow::loadMedia()
{
    bool lSuccess = true;
    m_pKeyPressSurfaces[ DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "../../../../resources/bmp/press.bmp" );
    if( m_pKeyPressSurfaces[ DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT ] == nullptr )
    {
        PRINT_ERROR("Failed to load default image!");
        lSuccess = false;
    }

    m_pKeyPressSurfaces[ DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_UP ] = loadSurface( "../../../../resources/bmp/up.bmp" );
    if( m_pKeyPressSurfaces[ DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_UP ] == nullptr )
    {
        PRINT_ERROR( "Failed to load up image!" );
        lSuccess = false;
    }

    m_pKeyPressSurfaces[ DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_DOWN ] = loadSurface( "../../../../resources/bmp/down.bmp" );
    if( m_pKeyPressSurfaces[ DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_DOWN ] == nullptr )
    {
        PRINT_ERROR( "Failed to load down image!" );
        lSuccess = false;
    }

    m_pKeyPressSurfaces[ DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_LEFT ] = loadSurface( "../../../../resources/bmp/left.bmp" );
    if( m_pKeyPressSurfaces[ DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_LEFT ] == nullptr )
    {
        PRINT_ERROR( "Failed to load left image!" );
        lSuccess = false;
    }

    m_pKeyPressSurfaces[ DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "../../../../resources/bmp/right.bmp" );
    if( m_pKeyPressSurfaces[ DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_RIGHT ] == nullptr )
    {
        PRINT_ERROR( "Failed to load right image!" );
        lSuccess = false;
    }

    return lSuccess;
}

void drkrWindow::close()
{
    for( unsigned int i = 0; i < DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_TOTAL; ++i )
    {
        SDL_FreeSurface( m_pKeyPressSurfaces[ i ] );
        m_pKeyPressSurfaces[ i ] = nullptr;
    }

    SDL_DestroyWindow( m_pWindow );
    m_pWindow = nullptr;

    SDL_Quit();
}

SDL_Surface* drkrWindow::loadSurface( std::string aPath )
{
    SDL_Surface* lOptimizedSurface = nullptr;

    SDL_Surface* lLoadedSurface = SDL_LoadBMP( aPath.c_str() );
    if( lLoadedSurface == nullptr )
    {
        PRINT_ERROR( SDL_GetError() );
    }
    else
    {
        lOptimizedSurface = SDL_ConvertSurface( lLoadedSurface, m_pScreenSurface->format, NULL );
        if( lOptimizedSurface == nullptr )
        {
            PRINT_ERROR( SDL_GetError() );
        }
        SDL_FreeSurface( lLoadedSurface );
    }
    return lOptimizedSurface;
}

void drkrWindow::setCurrentSurface( SDL_Surface * aSurface )
{
    m_pCurrentSurface = aSurface;
}

SDL_Surface * drkrWindow::getCurrentSurface()
{
    return m_pCurrentSurface;
}

SDL_Surface * drkrWindow::getSurface( DRKR::KeyPressSurfaces aSurfaceEnum )
{
    SDL_Surface* lRetVal = m_pKeyPressSurfaces[ aSurfaceEnum ];
    return lRetVal;
}

bool drkrWindow::updateWindow()
{
    SDL_Rect lStretchRect;
    lStretchRect.x = 0;
    lStretchRect.y = 0;
    lStretchRect.w = DRKR::SCREEN_WIDTH;
    lStretchRect.h = DRKR::SCREEN_HEIGHT;

    int lRetVal = SDL_BlitScaled( m_pCurrentSurface, NULL, m_pScreenSurface, &lStretchRect );
    if( DRKR_FAIL(lRetVal) )
    {
        PRINT_ERROR( SDL_GetError() );
        return false;
    }

    lRetVal = SDL_UpdateWindowSurface( m_pWindow );
    if( DRKR_FAIL( lRetVal ) )
    {
        PRINT_ERROR( SDL_GetError() );
        return false;
    }

    return true;
}

void drkrWindow::setSurface(const DRKR::KeyPressSurfaces aSurfaceEnum )
{
    setCurrentSurface( getSurface( aSurfaceEnum ) );
}
