#include "pch.h"
#include <iostream>
#include <list>
#include "DLLSimple.h"

class SecretData {
public:
	int id;
    char* dataArray;
	SecretData(int newId);
	bool addChar(char c);
	void clear();

private:
	int length;
	int maxSize = 64;
};

SecretData::SecretData(int newId) {
	dataArray = new char[maxSize];
	id = newId;
	length = 0;
}

bool SecretData::addChar(char c) {
	if (length >= maxSize)
		return false;

	*(dataArray + length) = c;
	length++;
	return true;
}

void SecretData::clear() {
	for (int i = 0; i < length; i++) {
		*(dataArray + i) = '\0';
	}
}

std::list<SecretData*> globalList;
int count = 0;

int createSecret()
{
	SecretData *newSecret = new SecretData(count);
	globalList.push_back(newSecret);
	return count++;
}

bool addCharToSecret(int id, char c) {
	for (std::list<SecretData*>::iterator it = globalList.begin(); it != globalList.end(); it++)
		if (id == (*it)->id)
			return (*it)->addChar(c);
	return false;
}

bool clearSecret(int id) {
	for (std::list<SecretData*>::iterator it = globalList.begin(); it != globalList.end(); it++) {
		if (id == (*it)->id) {
			(*it)->clear();
			delete (*it);
			globalList.remove((*it));
			return true;
		}
	}
	return false;
}