#include <list>
#include <iostream>
#include <windows.h>
#include <dpapi.h>
#include "CPPTesting.h"

class SecretData {
public:
	int id;
	DATA_BLOB* dataBlob;
	SecretData(int newId);
	bool addChar(char c);
	bool obfuscate();
	bool deobfuscate();
	void clearDataBlob();
	void clearAndDelete();

private:
	int length;
	int maxSize = 32;
};

SecretData::SecretData(int newId) {
	dataBlob = new DATA_BLOB;
	dataBlob->pbData = new BYTE[maxSize];
	dataBlob->cbData = maxSize;

	id = newId;
	length = 0;
}

bool SecretData::addChar(char c) {
	if (length >= maxSize)
		return false;

	*(dataBlob->pbData + length) = c;
	length++;
	return true;
}

bool SecretData::obfuscate()
{
	if (CryptProtectMemory(dataBlob->pbData, dataBlob->cbData, CRYPTPROTECTMEMORY_SAME_PROCESS))
	{
		return true;
	}
	return false;
}

bool SecretData::deobfuscate()
{
	if (CryptUnprotectMemory(dataBlob->pbData, dataBlob->cbData, CRYPTPROTECTMEMORY_SAME_PROCESS))
	{
		return true;
	}
	return false;
}

void SecretData::clearDataBlob() {
	for (unsigned int i = 0; i < dataBlob->cbData; i++) {
		dataBlob->pbData[i] = '\0';
	}
}

void SecretData::clearAndDelete() {
	clearDataBlob();
	delete dataBlob->pbData;
	delete dataBlob;
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

bool doApplicationWork(int id) {
	for (std::list<SecretData*>::iterator it = globalList.begin(); it != globalList.end(); it++)
		if (id == (*it)->id) {
			(*it)->deobfuscate();
			//Sleep(5000);
			std::cout << "Doing the application work!" << std::endl;
			(*it)->obfuscate();
			return true;
		}

	return false;
}

bool clearSecret(int id) {
	for (std::list<SecretData*>::iterator it = globalList.begin(); it != globalList.end(); it++) {
		if (id == (*it)->id) {
			(*it)->clearAndDelete();
			delete (*it);
			globalList.remove((*it));
			return true;
		}
	}
	return false;
}

int main() {
	char secret[] = "TOP SECRET DATA";
	
	int s = createSecret();
	for (int i = 0; i < std::strlen(secret); i++) {
		addCharToSecret(s, secret[i]);
	}

	obfuscateSecret(s);

	doApplicationWork(s);

	clearSecret(s);
	
	return 0;
}