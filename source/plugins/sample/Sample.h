#pragma once

#include <qcompilerdetection.h>

#if defined( QUARTZ_BASE )
 #define SAMPLE_PLUGIN_FUNC Q_DECL_EXPORT
#else
 #define SAMPLE_PLUGIN_FUNC Q_DECL_IMPORT
#endif
