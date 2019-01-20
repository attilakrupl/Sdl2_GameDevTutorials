#include <stdio.h>

#define DRKR_NOT(_aBool        ) (!(_aBool))
#define DRKR_FAIL(_aResult     ) ((_aResult)!=0)
#define DRKR_SUCCESS(_aResult  ) ((_aResult)==0)
#define DRKR_ISNULL(_aPointer  ) ((_aPointer)==nullptr)
#define PRINT_ERROR(_aError    ) printf("File: %s,\n Line: %d,\n Error: %s\n\n", __FILE__, __LINE__, _aError)
#define PRINT_WARNING(_aWarning) printf("File: %s,\n Line: %d,\n Warning: %s\n\n", __FILE__, __LINE__, _aWarning)