#ifndef MASON_WIN_EXPORT_H
#define MASON_WIN_EXPORT_H

#ifdef MASON_CORE_DLL
#define MASON_CORE_API __declspec(dllexport)
#else
#define MASON_CORE_API __declspec(dllimport)
#endif

#endif