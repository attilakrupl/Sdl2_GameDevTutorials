#pragma once

#include <string>
#include "h/enums.h"
#include "SDL_rect.h"

struct SDL_Window;
struct SDL_Renderer;
class drkrTexture;

class drkrWindow
{
public:
    drkrWindow();
    ~drkrWindow();

    bool init();
    bool loadMedia();
    void close();

    bool renderScreen();
private:
    SDL_Renderer* m_pRenderer           = nullptr;
    SDL_Window*   m_pWindow             = nullptr;
    SDL_Rect      m_pSpriteClips[ 4 ];
    drkrTexture*  m_pSpriteSheetTexture = nullptr;
};