#include "UdpQtServer.h"


UdpQtServer::UdpQtServer(QObject *parent, int localport) :
	QObject(parent)
{
	socket = new QUdpSocket(this);
	socket->bind(QHostAddress::Any, localport);

	initCodecs();
	videoHeight = 600;						       
	videoWidth = 800;						          
	initBuffers(videoWidth,videoHeight);
	connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}


UdpQtServer::~UdpQtServer(void)
{
	if(pCodecCtx)
        avcodec_close(pCodecCtx);
    if(pFormatCtx)
        avformat_close_input(&pFormatCtx);
    if(pFrame)
        av_free(pFrame);
    if(pFrameRGB)
        av_free(pFrameRGB);
    
	/*this->terminate();
	this->wait(1000);*/
	socket->disconnect();
	delete socket;

	delete[] videoPacket.data;
	av_free_packet(&videoPacket);
}

void UdpQtServer::run()//deprect
{
	//qDebug()<<"run";
	//while(1)
	//{
	//	size = socket->pendingDatagramSize();
	//	if(size>0)
	//	{
	//		buffer.resize(size);
	//		socket->readDatagram(buffer.data(), size,		
 //                        &sender, &senderPort);
	//	}

	//}
}

void UdpQtServer::initCodecs()
{
	pFormatCtx=0;
	pCodecCtx=0;
	pCodec=0;
	pFrame=0;
	temp=0;

	av_register_all();

	pCodec=avcodec_find_decoder(AV_CODEC_ID_MPEG2VIDEO);
	if(pCodec==NULL)
	qDebug()<<"couldntfind codec";

	pCodecCtx = avcodec_alloc_context3(pCodec);


	if (avcodec_open2(pCodecCtx,pCodec,NULL) < 0)
	qDebug()<<"codec not opened";

	pFrame=av_frame_alloc();
	pFrameRGB=av_frame_alloc();
}

void UdpQtServer::initBuffers(int width, int height)
{
	pCodecCtx->width = width;
	pCodecCtx->height = height;

	numBytes=avpicture_get_size(AV_PIX_FMT_ARGB,width,height);
	temp = (uint8_t *)av_realloc(temp,numBytes*sizeof(uint8_t));
	avpicture_fill((AVPicture*)pFrameRGB,temp,AV_PIX_FMT_ARGB,width,height);

	av_init_packet(&videoPacket);
	packetData = new char[100000];
}


void UdpQtServer::readyRead()
{
	size = socket->pendingDatagramSize();

	socket->readDatagram(packetData, size,		
                         &sender, &senderPort);
	videoPacket.data = (uint8_t*)packetData;
	videoPacket.size = size;
	avcodec_decode_video2(pCodecCtx,pFrame,&isFrameFinished,&videoPacket);
	if(isFrameFinished)
        {
          qDebug()<<"          dobra ramka, display emit";
		  avFrameConvert(pFrameRGB,pFrame,pCodecCtx);
		  displayFrame(pFrameRGB, videoWidth, videoHeight);
        };
}

void UdpQtServer::avFrameConvert(AVFrame *dst, AVFrame *src, AVCodecContext *ctx)
{
	struct SwsContext *context;
    context = sws_getContext(ctx->width, ctx->height,ctx->pix_fmt,ctx->width,
								ctx->height, PIX_FMT_RGB32, SWS_BICUBIC,0,0,0);
    sws_scale(context,(uint8_t**)src->data,src->linesize, 0, ctx->height,
									dst->data, dst->linesize);
    sws_freeContext(context);
}

void UdpQtServer::displayFrame(AVFrame *pFrame, int width, int height)
{
	QImage tempImg = QImage(width, height, QImage::Format_RGB32);
	for(int y=0; y<height; y++)
       memcpy(tempImg.scanLine(y), pFrame->data[0]+y*pFrame->linesize[0], width*4);

	//emit test(5);
	emit completeFrame(tempImg);
}


void UdpQtServer::HelloUDP()
{
    QByteArray Data;
    Data.append("Hello");
  
    socket->writeDatagram(Data, QHostAddress::LocalHost, 1234);
}