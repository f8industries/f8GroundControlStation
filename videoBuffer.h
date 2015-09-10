#pragma once

#include "myStructs.h"

#include <queue>
#include <iostream>

class videoBuffer
{
public:
	videoBuffer(void);
	~videoBuffer(void);

	int  getPlace();
	void forgetPlace();

	void addElement(metaDatagram);
	bool getElement(metaDatagram *meta);

	char dataBuffer[CAPACITY][MAX_DATAGRAM_LENGHT];

private:
	std::queue<metaDatagram> metaData;

	int sIterator;
	int lastIterator;


};

