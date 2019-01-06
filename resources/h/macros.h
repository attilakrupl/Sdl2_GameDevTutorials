#include <stdio.h>

#define DRKR_FAIL(x) x!=0
#define DRKR_SUCCESS(x) x==0
#define PRINT_ERROR(error) printf("File: %s,\n Line: %d,\n Error: %s\n\n", __FILE__, __LINE__, error)