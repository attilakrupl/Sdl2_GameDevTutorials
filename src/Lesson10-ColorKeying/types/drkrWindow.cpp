#include "drkrWindow.h"
#include "drkrTexture.h"
#include "h/macros.h"
#include "h/consts.h"

#include <SDL.h>
#include <SDL_image.h>

namespace
{
    bool handleRenderError( const int aRenderResult )
    {
        if( DRKR_FAIL( aRenderResult ) )
        {
            PRINT_ERROR( SDL_GetError() );
            return false;
        }
        return true;
    }
}

drkrWindow::drkrWindow()
{}

drkrWindow::~drkrWindow()
{}

bool drkrWindow::init()
{
    if( DRKR_FAIL( SDL_Init( SDL_INIT_VIDEO ) ) )
    {
        PRINT_ERROR( SDL_GetError() );
        return false;
    }

    if( DRKR_NOT( SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) )
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

    m_pFooTexture        = new drkrTexture( m_pRenderer );
    m_pBackgroundTexture = new drkrTexture( m_pRenderer );

    int lSetColorSuccess = SDL_SetRenderDrawColor( m_pRenderer
                                                 , DRKR::HEX_RED_COLOR_COMPONENT
                                                 , DRKR::HEX_GREEN_COLOR_COMPONENT
                                                 , DRKR::HEX_BLUE_COLOR_COMPONENT
                                                 , DRKR::HEX_OPACITY_COLOR_COMPONENT );
    if( DRKR_FAIL( lSetColorSuccess ) )
    {
        PRINT_WARNING( SDL_GetError() );
    }

    int imgFlags = IMG_INIT_PNG;
    if( DRKR_NOT( IMG_Init( imgFlags ) & imgFlags ) )
    {
        PRINT_ERROR( IMG_GetError() );
        return false;
    }
    return true;
}

bool drkrWindow::loadMedia()
{
    bool lSuccess = true;

    if( DRKR_NOT( m_pFooTexture->loadFromFile( "../../../../resources/png/foo.png" ) ) )
    {
        PRINT_ERROR( "Failed to load Foo's texture image!\n" );
        lSuccess = false;
    }

    if( DRKR_NOT( m_pBackgroundTexture->loadFromFile( "../../../../resources/png/background.png" ) ) )
    {
        PRINT_ERROR( "Failed to load background texture image!\n" );
        lSuccess = false;
    }

    return lSuccess;
}

void drkrWindow::close()
{
    m_pFooTexture->free();
    m_pBackgroundTexture->free();
    SDL_DestroyRenderer( m_pRenderer );
    SDL_DestroyWindow( m_pWindow );
    m_pRenderer = nullptr;
    m_pWindow = nullptr;

    IMG_Quit();
    SDL_Quit();
}

bool drkrWindow::renderScreen()
{
    bool lRenderSucceeded = true;

    int lRenderDrawColorResult = SDL_SetRenderDrawColor( m_pRenderer
                                                       , 0xFF
                                                       , 0xFF
                                                       , 0xFF
                                                       , 0xFF );
    if( DRKR_FAIL( lRenderDrawColorResult ) )
    {
        lRenderSucceeded = false;
        PRINT_ERROR( SDL_GetError() );
    }

    int lRendererClearResult = SDL_RenderClear( m_pRenderer );
    if( DRKR_FAIL( lRendererClearResult ) )
    {
        lRenderSucceeded = false;
        PRINT_ERROR( SDL_GetError() );
    }

    m_pBackgroundTexture->render( 0
                                , 0 );
 
    m_pFooTexture->render( 240  
                         , 190 );

    SDL_RenderPresent( m_pRenderer );

    return lRenderSucceeded;
}