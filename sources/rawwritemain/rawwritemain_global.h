#ifndef RAWWRITEMAIN_GLOBAL_H
#define RAWWRITEMAIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(RAWWRITEMAIN_LIBRARY)
#  define RAWWRITEMAIN_EXPORT Q_DECL_EXPORT
#else
#  define RAWWRITEMAIN_EXPORT Q_DECL_IMPORT
#endif

#endif // RAWWRITEMAIN_GLOBAL_H
