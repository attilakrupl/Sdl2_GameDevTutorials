#include "drkrEventHandler.h"
#include "drkrWindow.h"

#include "h/macros.h"

#include <SDL.h>

void drkrEventHandler::handleEvent( const SDL_Event* aEvent, bool& aShouldQuit )
{
    if( aEvent->type == SDL_QUIT )
    {
        aShouldQuit = true;
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
        if( !m_pWindow->renderScreen() )
        {
            PRINT_ERROR( "Failed to update window." );
            return false;
        }
    }
    return lQuit;
}
