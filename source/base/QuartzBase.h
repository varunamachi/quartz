#pragma once

#include <qcompilerdetection.h>

#if defined( QUARTZ_BASE )
 #define QUARTZ_BASE_API Q_DECL_EXPORT
#else
 #define QUARTZ_BASE_API Q_DECL_IMPORT
#endif
