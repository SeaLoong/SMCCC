#ifndef SMCCC_GLOBAL_H
#define SMCCC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SMCCC_LIBRARY)
#  define SMCCCSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SMCCCSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SMCCC_GLOBAL_H
