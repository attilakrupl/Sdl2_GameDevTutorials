#pragma once

#include <string>

struct SDL_Texture;
struct SDL_Renderer;

class drkrTexture
{
public:
    drkrTexture( SDL_Renderer* aSdlRenderer );
    ~drkrTexture();

    bool loadFromFile( std::string aPath );
    void free();
    void render( int aX, int aY );

    int getWidth();
    int getHeight();
private:
    SDL_Texture* mTexture;
    SDL_Renderer* mRenderer;

    int mWidth;
    int mHeight;
};