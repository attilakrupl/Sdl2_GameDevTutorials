#include "drkrWindow.h"
#include "h/macros.h"
#include "h/consts.h"

#include <SDL.h>
#include <SDL_image.h>

static const constexpr unsigned int HEX_MAX_COLOR_COMPONENT = 0xFF;

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

    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        PRINT_WARNING( "Linear texture filtering not enabled!" );
    }

    m_pWindow = SDL_CreateWindow( "SDL Tutorial"
                                , SDL_WINDOWPOS_UNDEFINED
                                , SDL_WINDOWPOS_UNDEFINED
                                , DRKR::SCREEN_WIDTH
                                , DRKR::SCREEN_HEIGHT
                                , SDL_WINDOW_SHOWN );
    if( DRKR_ISNULL( m_pWindow ) )
    {
        PRINT_ERROR( SDL_GetError() );
        return false;
    }

    m_pRenderer = SDL_CreateRenderer( m_pWindow
                                    , -1
                                    , SDL_RENDERER_ACCELERATED);
    if( DRKR_ISNULL( m_pRenderer ) )
    {
        PRINT_ERROR( SDL_GetError() );
        return false;
    }
    int lSetColorSuccess = SDL_SetRenderDrawColor( m_pRenderer
                                                 , HEX_MAX_COLOR_COMPONENT
                                                 , HEX_MAX_COLOR_COMPONENT
                                                 , HEX_MAX_COLOR_COMPONENT
                                                 , HEX_MAX_COLOR_COMPONENT );
    if( DRKR_FAIL( lSetColorSuccess ) )
    {
        PRINT_WARNING( SDL_GetError() );
    }

    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        PRINT_ERROR( IMG_GetError() );
        return false;
    }

    m_pScreenSurface = SDL_GetWindowSurface( m_pWindow );

    return true;
}

bool drkrWindow::loadMedia()
{
    bool lSuccess = true;
    m_pKeyPressSurfaces[ DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "../../../../resources/png/loaded.png" );
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

    m_pTexture = loadTexture( "../../../../resources/png/texture.png" );
    if( DRKR_ISNULL( m_pTexture ) )
    {
        PRINT_ERROR( "Failed to load texture image!\n" );
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

    SDL_DestroyTexture( m_pTexture );
    m_pTexture = nullptr;

    SDL_DestroyWindow( m_pWindow );
    m_pWindow = nullptr;

    IMG_Quit();
    SDL_Quit();
}

SDL_Surface* drkrWindow::loadSurface( std::string aPath )
{
    SDL_Surface* lOptimizedSurface = nullptr;

    SDL_Surface* lLoadedSurface = IMG_Load( aPath.c_str() );
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

SDL_Texture* drkrWindow::loadTexture( std::string aPath )
{
    SDL_Texture* lNewTexture = nullptr;
    SDL_Surface* lLoadedSurface = IMG_Load( aPath.c_str() );
    if( DRKR_ISNULL( lLoadedSurface ) )
    {
        PRINT_ERROR( SDL_GetError() );
    }
    else
    {
        lNewTexture = SDL_CreateTextureFromSurface( m_pRenderer, lLoadedSurface );
        if( DRKR_ISNULL( lNewTexture ) )
        {
            PRINT_ERROR( SDL_GetError() );
        }
        SDL_FreeSurface( lLoadedSurface );
    }
    return lNewTexture;
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
