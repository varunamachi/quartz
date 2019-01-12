#pragma once

#include <qcompilerdetection.h>

#if defined(QUARTZ_COMMON)
 #define QUARTZ_COMMON_API Q_DECL_EXPORT
#else
 #define QUARTZ_COMMON_API Q_DECL_IMPORT
#endif
