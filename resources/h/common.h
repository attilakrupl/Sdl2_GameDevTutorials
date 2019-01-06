#define DRKR_FAIL(x) x!=0
#define DRKR_SUCCESS(x) x==0
#define PRINT_ERROR(error) printf("File: %s,\n Line: %d,\n Error: %s\n\n", __FILE__, __LINE__, error)

namespace DRKR
{
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    enum KeyPressSurfaces
    {
        KEY_PRESS_SURFACE_DEFAULT,
        KEY_PRESS_SURFACE_UP,
        KEY_PRESS_SURFACE_DOWN,
        KEY_PRESS_SURFACE_LEFT,
        KEY_PRESS_SURFACE_RIGHT,
        KEY_PRESS_SURFACE_TOTAL
    };
}
