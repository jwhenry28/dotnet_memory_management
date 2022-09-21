#pragma once

#ifdef DLLSIMPLE_EXPORTS
#define DLLSIMPLE_API __declspec(dllexport)
#else
#define DLLSIMPLE_API __declspec(dllimport)
#endif


extern "C" DLLSIMPLE_API int createSecret();

extern "C" DLLSIMPLE_API bool addCharToSecret(int, char);

extern "C" DLLSIMPLE_API bool clearSecret(int);
