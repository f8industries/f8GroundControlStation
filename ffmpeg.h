#ifndef FFMPEG_H
#define FFMPEG_H


#include <stdint.h>



extern "C"
{
#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include "libavutil/mathematics.h"
#include <libavformat/avio.h>
#include <libavutil/file.h>

#include "libavutil/rational.h"
#include "libavutil/avstring.h"

#include <stdio.h>
}

#endif // FFMPEG_H