#pragma once

#include <QObject>
#include <QUdpSocket>
#include <QThread>
#include "ffmpeg.h"
#include <QPainter>
#include <stdio.h>
#include <cstdio>


class UdpQtServer : public QObject
{
	Q_OBJECT
public:
	UdpQtServer(QObject *parent , int localport);
	~UdpQtServer();
	void run();

	void HelloUDP();
signals:
    
public slots:
    void readyRead();

private:
	void initCodecs();
	void initBuffers(int width, int height);
    QUdpSocket *socket;
	QHostAddress sender;
    quint16 senderPort;

	QByteArray buffer;
	size_t size;

	AVFormatContext     *pFormatCtx;
	AVCodecContext      *pCodecCtx;
	AVCodec             *pCodec;
	AVFrame             *pFrame;
	AVFrame             *pFrameRGB;
	int                 numBytes;
	int                 currentWidth, currentHeight;
	uint8_t             *temp;
	AVPacket            videoPacket;
	char*				packetData;
	QImage              qFrame;
	SwsContext          *img_convert_ctx;

	int					isFrameFinished;
	int					videoWidth, videoHeight;
	/// decoded frame
	void avFrameConvert(AVFrame *dst, AVFrame *src, AVCodecContext *ctx);
	void displayFrame(AVFrame *pFrame, int width, int height);

signals:
	void test(int i);
	void completeFrame(QImage Image);

};

