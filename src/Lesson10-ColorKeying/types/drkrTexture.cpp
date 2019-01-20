#include "drkrTexture.h"
#include "h/macros.h"

#include <SDL.h>
#include <SDL_Image.h>

drkrTexture::drkrTexture( SDL_Renderer* aSdlRenderer ) :
    mTexture(nullptr),
    mWidth{0},
    mHeight{0},
    mRenderer{ aSdlRenderer }
{
}

drkrTexture::~drkrTexture()
{
    free();
}

bool drkrTexture::loadFromFile( std::string aPath )
{
    free();

    SDL_Texture* lNewTexture    = nullptr;
    SDL_Surface* lLoadedSurface = IMG_Load( aPath.c_str() );
    if( DRKR_ISNULL(lLoadedSurface) )
    {
        PRINT_ERROR( IMG_GetError() );
        return false;
    }

    SDL_bool lDoColorKey          = SDL_TRUE;
    Uint8    lRedColorComponent   = 0;
    Uint8    lGreenColorComponent = 0xFF;
    Uint8    lBlueColorComponent  = 0xFF;

    int lColorKeySetResult = SDL_SetColorKey( lLoadedSurface
                                            , SDL_TRUE
                                            , SDL_MapRGB( lLoadedSurface->format
                                                        , 0
                                                        , 0xFF
                                                        , 0xFF ) );
    if( DRKR_FAIL( lColorKeySetResult ) )
    {
        PRINT_ERROR( SDL_GetError() );
        return false;
    }

    lNewTexture = SDL_CreateTextureFromSurface( mRenderer
                                              , lLoadedSurface );
    if( DRKR_ISNULL( lNewTexture ) )
    {
        PRINT_ERROR(SDL_GetError());
    }
    mHeight = lLoadedSurface->h;
    mWidth =  lLoadedSurface->w;

    SDL_FreeSurface( lLoadedSurface );

    mTexture = lNewTexture;
    bool mTextureIsNull = DRKR_ISNULL( mTexture );
    return DRKR_NOT( mTextureIsNull );
}

void drkrTexture::free()
{
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = nullptr;
        mWidth   = 0;
        mHeight  = 0;
    }
}

void drkrTexture::render( int aX, int aY )
{
    SDL_Rect renderQuad = { aX
                          , aY
                          , mWidth
                          , mHeight };
    int lRenderResult = SDL_RenderCopy( mRenderer
                                      , mTexture
                                      , nullptr
                                      , &renderQuad );
    if( DRKR_FAIL( lRenderResult ) )
    {
        PRINT_ERROR( SDL_GetError() );
    }
}

int drkrTexture::getWidth()
{
    return mWidth;
}

int drkrTexture::getHeight()
{
    return mHeight;
}
