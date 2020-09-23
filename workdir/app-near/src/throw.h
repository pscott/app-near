#ifndef __THROW_H__
#define __THROW_H__

#ifdef OS_IO_SEPROXYHAL
    #include <os.h>
#else
    #define THROW(x) do { \
        printf("THROW(%d)\n", x); \
        exit(1); \
    } while (0);
#endif

#endif /* __THROW_H__ */