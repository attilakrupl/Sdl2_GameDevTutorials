#include "types/drkrWindow.h"

using namespace DRKR;

namespace DRKR
{
    void setSurface( drkrWindow& aWindow, const KeyPressSurfaces aSurfaceEnum )
    {
        aWindow.setCurrentSurface( aWindow.getSurface(aSurfaceEnum));
    }
}

int main( int argc, char* args[] )
{
    drkrWindow lWindow;

    if( !lWindow.init() )
    {
        PRINT_ERROR( "Failed to initialize!" );
        return -1;
    }
   
    if( !lWindow.loadMedia() )
    {
        PRINT_ERROR( "Failed to load media" );
        return -1;
    }

    bool lQuit = false;
    SDL_Event lEvent;
    setSurface( lWindow, KEY_PRESS_SURFACE_DEFAULT );

    while( !lQuit )
    {
        while( SDL_PollEvent( &lEvent ) != 0 )
        {
            if( lEvent.type == SDL_QUIT )
            {
                lQuit = true;
            }

            else if( lEvent.type == SDL_KEYDOWN )
            {
                switch( lEvent.key.keysym.sym )
                {
                case SDLK_UP:
                    setSurface( lWindow, KEY_PRESS_SURFACE_UP );
                    break;

                case SDLK_DOWN:
                    setSurface( lWindow, KEY_PRESS_SURFACE_DOWN );
                    break;

                case SDLK_LEFT:
                    setSurface( lWindow, KEY_PRESS_SURFACE_LEFT );
                    break;

                case SDLK_RIGHT:
                    setSurface( lWindow, KEY_PRESS_SURFACE_RIGHT );
                    break;

                default:
                    setSurface( lWindow, KEY_PRESS_SURFACE_DEFAULT );
                    break;
                }
            }
        }
        if( !lWindow.updateWindow() )
        {
            PRINT_ERROR( "Failed to update window." );
            return -1;
        }
    }
    lWindow.close();
    return 0;
}