#include "pch.h"
#include <list>
#include <iostream>
#include <string>
#include "DLLHashing.h"
#include "sha256.h"

class SecretData {
public:
	int id;
	char* dataArray;
	bool dataArrayCleared;
	unsigned char* hashArray;
	bool hashArrayCleared;
	SecretData(int newId);
	bool addChar(char c);
	void obfuscate();
	void clearHashArray();

private:
	int length;
	int maxSize = 32;
	int hashSize = 32;
	void clearDataArray();
};

SecretData::SecretData(int newId) {
	dataArray = new char[maxSize];
	id = newId;
	length = 0;
	dataArrayCleared = false;
	hashArrayCleared = true;
}

bool SecretData::addChar(char c) {
	if (length >= maxSize)
		return false;

	*(dataArray + length) = c;
	length++;
	return true;
}

void SecretData::obfuscate()
{
	addChar('\0');
	hashArray = new unsigned char[hashSize+1];
	hashArrayCleared = false;

	SHA256 sha256;
	sha256(dataArray);
	sha256.getHash(hashArray);
	hashArray[hashSize] = '\0';

	clearDataArray();
}

void SecretData::clearDataArray() {
	if (dataArrayCleared)
		return;

	for (int i = 0; i < length; i++) {
		*(dataArray + i) = '\0';
	}
	delete dataArray;
	dataArrayCleared = true;
}

void SecretData::clearHashArray() {
	if (hashArrayCleared)
		return;

	for (int i = 0; i < hashSize; i++) {
		*(hashArray + i) = '\0';
	}
	delete hashArray;
	hashArrayCleared = true;
}

std::list<SecretData*> globalList;
int count = 0;

int createSecret()
{
	SecretData* newSecret = new SecretData(count);
	globalList.push_back(newSecret);
	return count++;
}

bool addCharToSecret(int id, char c) {
	for (std::list<SecretData*>::iterator it = globalList.begin(); it != globalList.end(); it++)
		if (id == (*it)->id)
			return (*it)->addChar(c);
	return false;
}

bool obfuscateSecret(int id) {
	for (std::list<SecretData*>::iterator it = globalList.begin(); it != globalList.end(); it++)
		if (id == (*it)->id) {
			(*it)->obfuscate();
			return true;
		}
	return false;
}

bool compareSecret(int id, char* input) {
	SHA256 sha256;
	const int hashSize = 32;
	unsigned char inputHash[hashSize];
	sha256(input);
	sha256.getHash(inputHash);

	for (std::list<SecretData*>::iterator it = globalList.begin(); it != globalList.end(); it++)
		if (id == (*it)->id) {
			for (int i = 0; i < hashSize; i++)
				if ((*it)->hashArray[i] != inputHash[i]) 
					return false;
			return true;
		}

	return false;
}

std::string toHexStr(unsigned char* hash, int len) {
	static const char dec2hex[16 + 1] = "0123456789abcdef";
	std::string res = "";
	for (int i = 0; i < len; i++)
	{
		res += dec2hex[(hash[i] >> 4) & 15];
		res += dec2hex[hash[i] & 15];
	}

	return res;
}

bool clearSecret(int id) {
	for (std::list<SecretData*>::iterator it = globalList.begin(); it != globalList.end(); it++) {
		if (id == (*it)->id) {
			(*it)->clearHashArray();
			delete (*it);
			globalList.remove((*it));
			return true;
		}
	}
	return false;
}