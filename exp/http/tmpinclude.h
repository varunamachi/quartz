#pragma once

#ifdef _WIN32
    #ifndef _CRT_SECURE_NO_WARNINGS
        #define _CRT_SECURE_NO_WARNINGS
    #endif
    #ifndef _CRT_NONSTDC_NO_DEPRECATE
        #define _CRT_NONSTDC_NO_DEPRECATE
    #endif
    #if defined(_MSC_VER) && _MSC_VER < 1900
        #define snprintf _snprintf_s
    #endif
    #ifndef S_ISREG
        #define S_ISREG(m) (((m)&S_IFREG) == S_IFREG)
    #endif
    #ifndef S_ISDIR
        #define S_ISDIR(m) (((m)&S_IFDIR) == S_IFDIR)
    #endif

    #define WIN32_LEAN_AND_MEAN
    #include <io.h>
    #include <winsock2.h>
    #include <ws2tcpip.h>

    #undef min
    #undef max

typedef SOCKET socket_t;
#else
    #include <pthread.h>
    #include <unistd.h>
    #include <netdb.h>
    #include <cstring>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <signal.h>
    #include <sys/socket.h>

typedef int socket_t;
#endif
