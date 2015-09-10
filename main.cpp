#include "f8gcs.h"
#include <QtWidgets/QApplication>

#include "UdpQtServer.h"
//#include "UdpServer.h"//todo

#include "videoBuffer.h"
#include "videoDecoder.h"
#include <boost/thread/thread.hpp>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	UdpQtServer client(0, 1234);///qt -wolny ale dziala	

	//client.start();

	//UdpServer udpServer(1236);///socket na boost, nie dzia³a przy localhoscie, chyba zajmuje ten sam port co nadawca

	//gui
	f8GCS w;
	w.show();
	//w.showMaximized();

	QObject::connect(&client,SIGNAL(completeFrame(QImage)),&w,SLOT(displayFrame(QImage)));

	return a.exec();
}
