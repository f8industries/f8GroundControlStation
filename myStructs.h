#pragma once

#include <boost\array.hpp>

#define CAPACITY 100
#define MAX_DATAGRAM_LENGHT 2000

struct metaDatagram
{
  char *dataHead_;
  size_t size_;
};


