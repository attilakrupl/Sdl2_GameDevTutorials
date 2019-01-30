#include "types/drkrWindow.h"
#include "types/drkrEventHandler.h"
#include "h/macros.h"

int main( int argc, char** argv )
{
    drkrWindow lWindow;
    if( DRKR_NOT ( lWindow.init() ) )
    {
        printf( "Failed to initialize!\n" );
        return -1;
    }
    if( DRKR_NOT( lWindow.loadMedia() ) )
    {
        printf( "Failed to load media!\n" );
        return -1;
    }

    drkrEventHandler lEventHandler( &lWindow );
    if( DRKR_NOT( lEventHandler.runEventLoop() ) )
    { 
        PRINT_ERROR( "Event loop run into an error." );
        return -1;
    }

    lWindow.close();
    return 0;
}