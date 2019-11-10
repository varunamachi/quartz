

#pragma once

#if defined(QUARTZ_EXT)
    #define QZ_CORE_EXPORT Q_DECL_EXPORT
#else
    #define QZ_CORE_EXPORT Q_DECL_IMPORT
#endif
