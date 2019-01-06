#include "drkrWindow.h"

drkrWindow::drkrWindow()
{}

drkrWindow::~drkrWindow()
{}

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
        , DRKR::SCREEN_WIDTH
        , DRKR::SCREEN_HEIGHT
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
    m_pKeyPressSurfaces[ DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "../../../../resources/bmp/press.bmp" );
    if( m_pKeyPressSurfaces[ DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT ] == nullptr )
    {
        printf( "Failed to load default image!\n" );
        lSuccess = false;
    }

    m_pKeyPressSurfaces[ DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_UP ] = loadSurface( "../../../../resources/bmp/up.bmp" );
    if( m_pKeyPressSurfaces[ DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_UP ] == nullptr )
    {
        printf( "Failed to load up image!\n" );
        lSuccess = false;
    }

    m_pKeyPressSurfaces[ DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_DOWN ] = loadSurface( "../../../../resources/bmp/down.bmp" );
    if( m_pKeyPressSurfaces[ DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_DOWN ] == nullptr )
    {
        printf( "Failed to load down image!\n" );
        lSuccess = false;
    }

    m_pKeyPressSurfaces[ DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_LEFT ] = loadSurface( "../../../../resources/bmp/left.bmp" );
    if( m_pKeyPressSurfaces[ DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_LEFT ] == nullptr )
    {
        printf( "Failed to load left image!\n" );
        lSuccess = false;
    }

    m_pKeyPressSurfaces[ DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "../../../../resources/bmp/right.bmp" );
    if( m_pKeyPressSurfaces[ DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_RIGHT ] == nullptr )
    {
        printf( "Failed to load right image!\n" );
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
    SDL_Surface* lLoadedSurface = SDL_LoadBMP( aPath.c_str() );
    if( lLoadedSurface == nullptr )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", aPath.c_str(), SDL_GetError() );
    }

    return lLoadedSurface;
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
    int lRetVal = SDL_BlitSurface( m_pCurrentSurface, NULL, m_pScreenSurface, NULL );
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
