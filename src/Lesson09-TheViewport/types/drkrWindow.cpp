#include "drkrWindow.h"
#include "h/macros.h"
#include "h/consts.h"

#include <SDL.h>
#include <SDL_image.h>

static const constexpr unsigned int HEX_MAX_COLOR_COMPONENT = 0xFF;
static const constexpr unsigned int HEX_RED_COLOR_COMPONENT = 0x2F;
static const constexpr unsigned int HEX_GREEN_COLOR_COMPONENT = 0x48;
static const constexpr unsigned int HEX_BLUE_COLOR_COMPONENT = 0xe2;

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
                                                 , HEX_RED_COLOR_COMPONENT
                                                 , HEX_GREEN_COLOR_COMPONENT
                                                 , HEX_BLUE_COLOR_COMPONENT
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
    return true;
}

bool drkrWindow::loadMedia()
{
    bool lSuccess = true;

    m_pTexture = loadTexture( "../../../../resources/png/viewport.png" );
    if( m_pTexture == NULL )
    {
        printf( "Failed to load texture image!\n" );
        lSuccess = false;
    }

    return lSuccess;
}

void drkrWindow::close()
{
    SDL_DestroyTexture( m_pTexture );
    SDL_DestroyRenderer( m_pRenderer );
    SDL_DestroyWindow( m_pWindow );
    m_pTexture = nullptr;
    m_pRenderer = nullptr;
    m_pWindow = nullptr;

    IMG_Quit();
    SDL_Quit();
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

bool drkrWindow::renderScreen()
{
    bool lRenderSucceeded  = true;
 
    int lRenderResult = SDL_SetRenderDrawColor( m_pRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    lRenderSucceeded &= handleRenderError( lRenderResult );
        lRenderResult = SDL_RenderClear( m_pRenderer );
    lRenderSucceeded &= handleRenderError( lRenderResult );

    SDL_Rect lTopLeftViewport{ 0, 0, DRKR::SCREEN_WIDTH / 2 , DRKR::SCREEN_HEIGHT / 2 };
    lRenderResult     = SDL_RenderSetViewport( m_pRenderer, &lTopLeftViewport );
    lRenderSucceeded &= handleRenderError( lRenderResult );
    lRenderResult     = SDL_RenderCopy( m_pRenderer, m_pTexture, NULL, NULL );
    lRenderSucceeded &= handleRenderError( lRenderResult );

    SDL_Rect lTopRightViewport{ DRKR::SCREEN_WIDTH / 2 , 0, DRKR::SCREEN_WIDTH / 2, DRKR::SCREEN_HEIGHT / 2 };
    lRenderResult     = SDL_RenderSetViewport( m_pRenderer, &lTopRightViewport );
    lRenderSucceeded &= handleRenderError( lRenderResult );
    lRenderResult     = SDL_RenderCopy( m_pRenderer, m_pTexture, NULL, NULL );
    lRenderSucceeded &= handleRenderError( lRenderResult );

    SDL_Rect bottomViewport{0, DRKR::SCREEN_HEIGHT / 2, DRKR::SCREEN_WIDTH, DRKR::SCREEN_HEIGHT / 2 };
    lRenderResult     = SDL_RenderSetViewport( m_pRenderer, &bottomViewport );
    lRenderSucceeded &= handleRenderError( lRenderResult );
    lRenderResult     = SDL_RenderCopy( m_pRenderer, m_pTexture, NULL, NULL );
    lRenderSucceeded &= handleRenderError( lRenderResult );

    SDL_RenderPresent( m_pRenderer );

    return lRenderSucceeded;
}
