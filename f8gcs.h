#ifndef F8GCS_H
#define F8GCS_H

#include <QtWidgets/QWidget>
#include "ui_f8gcs.h"
#include "qcgaugewidget.h"

#include <qdebug.h>
#include "SystemParameters.h"

//#include "UdpServer.h"
#include "UdpQtServer.h"

class f8GCS : public QWidget
{
	Q_OBJECT

public:
	f8GCS(QWidget *parent = 0);
	~f8GCS();

	//tymczasowo public
	QcGaugeWidget * mAttitudeGauge;
    QcNeedleItem * mAttitudeNeedle;
    QcAttitudeMeter *mAttMeter;
	QGraphicsScene *scene;

private:
	Ui::f8GCSClass ui;

	void createGauge();

	void setConnections();
	void setParams();
	void setUdp();

	void image2Pixmap(QImage &img,QPixmap &pixmap);
    

	SystemParameters params;

public slots:
	void setVideoView();
	void setMapView();
	void setPlotView();
	void changeCurrentIndex(int idx);

	void changeLabel(int i);
	void displayFrame(QImage);
    

	
};

#endif // F8GCS_H
