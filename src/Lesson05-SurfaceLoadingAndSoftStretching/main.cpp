#include "types/drkrWindow.h"
#include "types/drkrEventHandler.h"
#include "h/macros.h"

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

    lWindow.setSurface( DRKR::KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT );

    drkrEventHandler lEventHandler( &lWindow );
    lEventHandler.runEventLoop();

    lWindow.close();
    return 0;
}