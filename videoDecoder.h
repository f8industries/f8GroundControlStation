#pragma once

#include "videoBuffer.h"
#include "myStructs.h"
#include <qdebug.h>

class videoDecoder
{
public:
	videoDecoder(videoBuffer *buffer);
	~videoDecoder(void);

	void run();

private:
	videoBuffer *buffer_;
	metaDatagram meta;
};

