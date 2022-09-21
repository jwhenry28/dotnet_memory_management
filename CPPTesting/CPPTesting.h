#pragma once
#pragma comment(lib, "crypt32.lib")

int createSecret();

bool addCharToSecret(int, char);

bool clearSecret(int);

bool obfuscateSecret(int);

bool doApplicationWork(int);