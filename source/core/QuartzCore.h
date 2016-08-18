#pragma once

#if defined( QUARTZ_CORE )
 #define QUARTZ_CORE_API Q_DECL_EXPORT
#else
 #define QUARTZ_CORE_API Q_DECL_IMPORT
#endif
