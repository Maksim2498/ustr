#ifndef USTR_UTIL_EXPORT_H
#define USTR_UTIL_EXPORT_H

#include <ustr/config.h>

#ifdef USTR_WIN
    #define UEXPORT __declspec(dllexport)
#else
    #define UEXPORT
#endif

#endif