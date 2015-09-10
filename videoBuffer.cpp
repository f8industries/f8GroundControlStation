#include "videoBuffer.h"


videoBuffer::videoBuffer(void)
{
	sIterator = 0;
	lastIterator = 0;
}


videoBuffer::~videoBuffer(void)
{
}

int videoBuffer::getPlace()
{
	if(sIterator == CAPACITY)
    sIterator=0;
	return sIterator++;
}

void videoBuffer::addElement(metaDatagram meta_)
{
	metaData.push(meta_);
}

bool videoBuffer::getElement(metaDatagram *meta)
{
	metaDatagram temp;

	if(metaData.empty())
		return 0;
	else
	{
		meta->dataHead_ = metaData.front().dataHead_;
		meta->size_ = metaData.front().size_;
		return 1;
	}
}

void videoBuffer::forgetPlace()
{
	metaData.pop();
}
