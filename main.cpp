#include "f8gcs.h"
#include <QtWidgets/QApplication>

#include "UdpQtServer.h"
#include "UdpServer.h"


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	/*UdpQtServer client;
	client.HelloUDP();*/
	UdpServer udpServer(1235);



	f8GCS w;
	w.show();
	//w.showMaximized();
	return a.exec();
}
