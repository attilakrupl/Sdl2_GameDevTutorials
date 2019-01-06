#include "drkrWindow.h"

int main( int argc, char* argv[] )
{
    drkrWindow lWindow;
    if( !lWindow.init() )
    {
        printf( "Failed to initialize!\n" );
        return -1;
    }

    if( !lWindow.loadMedia() )
    {
        printf( "Failed to load media!\n" );
        return -1;
    }

    SDL_Delay( 2000 );

    lWindow.close();
    return 0;
}