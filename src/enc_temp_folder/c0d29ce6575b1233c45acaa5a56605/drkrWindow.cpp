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

    m_pWindow = SDL_CreateWindow( "SDL Clip Rendering Tutorial"
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
    bool lSuccess              = true;
         m_pSpriteSheetTexture = new drkrTexture( m_pRenderer );
    if( DRKR_NOT( m_pSpriteSheetTexture->loadFromFile( "../../../../resources/png/dots.png" ) ) )
    {
        PRINT_ERROR( "Failed to load Foo's texture image!\n" );
        lSuccess = false;
    }
    else
    {
        m_pSpriteClips[ 0 ]->x = 0;
        m_pSpriteClips[ 0 ]->y = 0;
        m_pSpriteClips[ 0 ]->w = 100;
        m_pSpriteClips[ 0 ]->h = 100;

        m_pSpriteClips[ 1 ]->x = 100;
        m_pSpriteClips[ 1 ]->y = 0;
        m_pSpriteClips[ 1 ]->w = 100;
        m_pSpriteClips[ 1 ]->h = 100;

        m_pSpriteClips[ 2 ]->x = 0;
        m_pSpriteClips[ 2 ]->y = 100;
        m_pSpriteClips[ 2 ]->w = 100;
        m_pSpriteClips[ 2 ]->h = 100;

        m_pSpriteClips[ 3 ]->x = 100;
        m_pSpriteClips[ 3 ]->y = 100;
        m_pSpriteClips[ 3 ]->w = 100;
        m_pSpriteClips[ 3 ]->h = 100;
    }
    return lSuccess;
}

void drkrWindow::close()
{
    m_pSpriteSheetTexture->free();
    SDL_DestroyRenderer( m_pRenderer );
    SDL_DestroyWindow( m_pWindow );
    m_pRenderer = nullptr;
    m_pWindow = nullptr;

    IMG_Quit();
    SDL_Quit();
}

bool drkrWindow::renderScreen()
{
    int lRenderDrawColorResult = SDL_SetRenderDrawColor( m_pRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    if( DRKR_FAIL( lRenderDrawColorResult ) )
    {
        return false;
        PRINT_ERROR( SDL_GetError() );
    }

    int lRenderClearResult     = SDL_RenderClear( m_pRenderer );
    if( DRKR_FAIL( lRenderClearResult ) )
    {
        return false;
        PRINT_ERROR( SDL_GetError() );
    }

    m_pSpriteSheetTexture->render( 0, 0, m_pSpriteClips[ 0 ] );
    m_pSpriteSheetTexture->render( DRKR::SCREEN_WIDTH - m_pSpriteClips[ 1 ]->w, 0, m_pSpriteClips[ 1 ] );
    m_pSpriteSheetTexture->render( 0, DRKR::SCREEN_HEIGHT - m_pSpriteClips[ 2 ]->h, m_pSpriteClips[ 2 ] );
    m_pSpriteSheetTexture->render( DRKR::SCREEN_WIDTH - m_pSpriteClips[ 3 ]->w, DRKR::SCREEN_HEIGHT - m_pSpriteClips[ 3 ]->h, m_pSpriteClips[ 3 ] );

    SDL_RenderPresent( m_pRenderer );

    return true;
}