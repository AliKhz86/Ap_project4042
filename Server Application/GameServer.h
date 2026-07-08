#pragma once
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <qobject.h>
#include <qthread.h>
#include "ServerRequestHandler.h"
#include "ServerStorage.h"

class GameServer : public QTcpServer {
	Q_OBJECT

private:
	QHostAddress _serverAddress;
	quint16 _port;
	QVector<QTcpSocket*> _clients;

public:
	GameServer(char* serverAddress, int port, QObject* parent = nullptr);

protected:
	void incomingConnection(qintptr socketDescriptor) override;

public slots:
	void ClientDisconnected();
	void ReadData();
};