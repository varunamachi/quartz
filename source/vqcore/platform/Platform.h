#pragma once

#ifdef _WIN32
    #define VQ_WINDOWS
    #define VQ_WIN_32
#elif _WIN64
    #define VQ_WINDOWS
    #define VQ_WIN_64
#elif __linux
    #define VQ_LINUX
    #define VQ_POSIX
#elif __APPLE__
    #define VQ_MAC_OS
    #define VQ_POSIX
#endif
