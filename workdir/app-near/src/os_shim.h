#ifndef __OS_SHIM_H__
#define __OS_SHIM_H__

#ifdef OS_IO_SEPROXYHAL
    #include <os.h>
#else
    #include <stdlib.h>
    #define THROW(x) do { \
        printf("THROW(%d)\n", x); \
        exit(1); \
    } while (0);

    #include <stdio.h>
    #define PRINTF printf

    #include <string.h>
    #define os_memmove memmove
    #define os_memset memset    
#endif

#endif /* __OS_SHIM_H__ */