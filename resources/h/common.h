#include <string>

static std::string DRKR_BMP_PATH_ROOT = "../../resources/bmp/";

namespace DRKR
{
    static const char* COMPOSE_PATH( const std::string& aRootPath, const std::string& aFileName )
    {
        std::string lResult = aRootPath;
        lResult.append( aFileName );
        return lResult.c_str();
    }
}