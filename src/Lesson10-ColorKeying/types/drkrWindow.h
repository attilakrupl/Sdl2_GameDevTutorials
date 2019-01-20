#pragma once

#include <string>
#include "h/enums.h"

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
    SDL_Renderer* m_pRenderer       = nullptr;
    SDL_Window*   m_pWindow         = nullptr;

    drkrTexture*  m_pFooTexture        = nullptr;
    drkrTexture*  m_pBackgroundTexture = nullptr;
};