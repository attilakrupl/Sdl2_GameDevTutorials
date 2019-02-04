#include "drkrEventHandler.h"
#include "drkrWindow.h"

#include "h/macros.h"

#include <SDL.h>

static Uint8 gREDMAX   = 255;
static Uint8 gGREENMAX = 255;
static Uint8 gBLUEMAX  = 255;

void drkrEventHandler::handleEvent( const SDL_Event* aEvent, bool& aShouldQuit )
{
    if( aEvent->type == SDL_QUIT )
    {
        aShouldQuit = true;
    }
    else if( aEvent->type == SDL_KEYDOWN )
    {
        switch( aEvent->key.keysym.sym )
        {
        case SDLK_q:
            gREDMAX += 32;
            break;

        case SDLK_w:
            gGREENMAX += 32;
            break;

        case SDLK_e:
            gBLUEMAX += 32;
            break;

        case SDLK_a:
            gREDMAX -= 32;
            break;

        case SDLK_s:
            gGREENMAX -= 32;
            break;

        case SDLK_d:
            gBLUEMAX -= 32;
            break;
        }
    }
}

drkrEventHandler::drkrEventHandler( drkrWindow * aWindow ) :
    m_pWindow(aWindow)
{
}

bool drkrEventHandler::runEventLoop()
{
    bool lQuit = false;
    SDL_Event lEvent;
    while( !lQuit )
    {
        while( SDL_PollEvent( &lEvent ) != 0 )
        {
            handleEvent( &lEvent, lQuit );
        }
        if( !m_pWindow->renderScreen( gREDMAX, gGREENMAX, gBLUEMAX ) )
        {
            PRINT_ERROR( "Failed to update window." );
            return false;
        }
    }
    return lQuit;
}
