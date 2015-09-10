#include "f8gcs.h"

f8GCS::f8GCS(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	setConnections();
	setParams();
	

	
	//setUdp();

	//UdpServer udpServer(1234);

}

f8GCS::~f8GCS()
{	
}

void f8GCS::setConnections()
{
	connect(ui.videoButton,SIGNAL(clicked()),this, SLOT(setVideoView()));
	connect(ui.mapButton,SIGNAL(clicked()),this,SLOT(setMapView()));
	connect(ui.plotsButton,SIGNAL(clicked()),this,SLOT(setPlotView()));
}

void f8GCS::setParams()
{
		/*params.createSchema();*/
	//qDebug()<< params.getValue(QString("telemetry/adress")); //
}

void f8GCS::setUdp()
{
	//UdpQtServer udpServer;

	//udpServer.HelloUDP();
}

void f8GCS::createGauge()
{
	mAttitudeGauge = new QcGaugeWidget;
    mAttitudeGauge->addBackground(99);
    QcBackgroundItem *bkg = mAttitudeGauge->addBackground(92);
    bkg->clearrColors();
    bkg->addColor(0.1,Qt::black);
    bkg->addColor(1.0,Qt::white);
    mAttMeter = mAttitudeGauge->addAttitudeMeter(88);

    mAttitudeNeedle = mAttitudeGauge->addNeedle(70);
    mAttitudeNeedle->setMinDegree(0);
    mAttitudeNeedle->setMaxDegree(180);
    mAttitudeNeedle->setValueRange(0,180);
    mAttitudeNeedle->setCurrentValue(90);
    mAttitudeNeedle->setColor(Qt::white);
    mAttitudeNeedle->setNeedle(QcNeedleItem::AttitudeMeterNeedle);
    mAttitudeGauge->addGlass(80);
}


void f8GCS::setVideoView()
{
	changeCurrentIndex(0);
}

void f8GCS::setMapView()
{
	changeCurrentIndex(1);
}

void f8GCS::setPlotView()
{
	changeCurrentIndex(2);
}

void f8GCS::changeCurrentIndex(int index_)
{
	qDebug()<<"change to "<<index_;
	if(ui.mainStackedWidget->currentIndex() != index_) 
	{
		ui.mainStackedWidget->setCurrentIndex(index_);
		ui.sideStackedWidget->setCurrentIndex(index_);
	}
}

void f8GCS::changeLabel(int i)
{
	ui.errorLabel->setText(QString::number(i));

}

void f8GCS::image2Pixmap(QImage &img,QPixmap &pixmap)
{
    pixmap = QPixmap(img.size());
    QPainter painter;
    painter.begin(&pixmap);
    painter.drawImage(0,0,img);
    painter.end();
}

void f8GCS::displayFrame(QImage frame)
{
    QPixmap p;
    image2Pixmap(frame,p);
	ui.videoLabel->setPixmap(p);
   // ui->labelVideoFrame->setPixmap(p);
}
