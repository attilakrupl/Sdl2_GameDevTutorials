#include <stdio.h>

#define DRKR_FAIL(x) x!=0
#define DRKR_SUCCESS(x) x==0
#define DRKR_ISNULL(x) x==nullptr
#define PRINT_ERROR(_aError) printf("File: %s,\n Line: %d,\n Error: %s\n\n", __FILE__, __LINE__, _aError)
#define PRINT_WARNING(_aWarning) printf("File: %s,\n Line: %d,\n Warning: %s\n\n", __FILE__, __LINE__, _aWarning)