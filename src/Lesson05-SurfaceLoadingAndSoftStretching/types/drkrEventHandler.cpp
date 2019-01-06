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

    else if( aEvent->type == SDL_KEYDOWN )
    {
        switch( aEvent->key.keysym.sym )
        {
        case SDLK_UP:
            m_pWindow->setSurface( DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_UP );
            break;

        case SDLK_DOWN:
            m_pWindow->setSurface( DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_DOWN );
            break;

        case SDLK_LEFT:
            m_pWindow->setSurface( DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_LEFT );
            break;

        case SDLK_RIGHT:
            m_pWindow->setSurface( DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_RIGHT );
            break;

        default:
            m_pWindow->setSurface( DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT );
            break;
        }
    }
}

drkrEventHandler::drkrEventHandler( drkrWindow * aWindow ) :
    m_pWindow(aWindow)
{
}

void drkrEventHandler::runEventLoop()
{
    bool lQuit = false;
    while( !lQuit )
    {
        SDL_Event lEvent;
        while( SDL_PollEvent( &lEvent ) != 0 )
        {
            handleEvent( &lEvent, lQuit );
        }
        if( !m_pWindow->updateWindow() )
        {
            PRINT_ERROR( "Failed to update window." );
        }
    }
}
