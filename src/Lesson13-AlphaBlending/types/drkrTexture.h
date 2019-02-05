#pragma once

#include <string>

#include "SDL_blendmode.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class drkrTexture
{
public:
    drkrTexture( SDL_Renderer* aSdlRenderer );
    ~drkrTexture();

    bool loadFromFile( std::string aPath );
    void free();
    void setColor( uint8_t aRed, uint8_t aGreen, uint8_t aBlue);
    void setBlendMode( SDL_BlendMode aBlending );
    void setAlpha( uint8_t aAlpha );
    void render( int aX, int aY, SDL_Rect* aClip = nullptr );

    int getWidth();
    int getHeight();
private:
    SDL_Texture*  mTexture;
    SDL_Renderer* mRenderer;

    int mWidth;
    int mHeight;
};