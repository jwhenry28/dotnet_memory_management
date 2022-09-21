#pragma once

#ifdef DLLHASHING_EXPORTS
#define DLLHASHING_API __declspec(dllexport)
#else
#define DLLHASHING_API __declspec(dllimport)
#endif


extern "C" DLLHASHING_API int createSecret();

extern "C" DLLHASHING_API bool addCharToSecret(int, char);

extern "C" DLLHASHING_API bool clearSecret(int);

extern "C" DLLHASHING_API bool obfuscateSecret(int);

extern "C" DLLHASHING_API bool compareSecret(int, char*);

std::string toHexStr(unsigned char*, int);