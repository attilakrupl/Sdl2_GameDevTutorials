#pragma once

#include <string>
#include "h/enums.h"

struct SDL_Window;
struct SDL_Texture;
struct SDL_Renderer;

class drkrWindow
{
public:
    drkrWindow();
    ~drkrWindow();

    bool init();
    bool loadMedia();
    void close();
    SDL_Texture* loadTexture( std::string aPath );

    bool renderScreen();

private:
    SDL_Renderer* m_pRenderer       = nullptr;
    SDL_Texture*  m_pTexture        = nullptr;
    SDL_Window*   m_pWindow         = nullptr;
};