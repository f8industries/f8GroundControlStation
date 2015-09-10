#include "videoDecoder.h"


videoDecoder::videoDecoder(videoBuffer *buffer)
{
	buffer_ = buffer;
}


videoDecoder::~videoDecoder(void)
{
}

void videoDecoder::run()
{
	while(true)
	{
		if(buffer_->getElement(&meta))///if 1 ready to decode
		{
			qDebug()<<" datagram size: "<< meta.size_;
			buffer_->forgetPlace();
		}

	}
}
