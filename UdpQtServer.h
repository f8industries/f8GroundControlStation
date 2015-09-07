#pragma once

#include <QObject>
#include <QUdpSocket>

class UdpQtServer : public QObject
{
	Q_OBJECT
public:
	explicit UdpQtServer(QObject *parent = 0);
	~UdpQtServer();
	void HelloUDP();
signals:
    
public slots:
    void readyRead();

private:
    QUdpSocket *socket;
};

