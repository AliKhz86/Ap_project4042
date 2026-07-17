#include "GameServer.h"

GameServer::GameServer(char* serverAddress, int port, QObject* parent): QTcpServer(parent)
{
	_serverAddress = QHostAddress(serverAddress);
	_port = port;
	listen(_serverAddress, _port);
}

void GameServer::incomingConnection(qintptr socketDescriptor)
{
	QTcpSocket* socket = new QTcpSocket(this);
	socket->setSocketDescriptor(socketDescriptor);
	_clients.push_back(socket);
	connect(socket, &QTcpSocket::disconnected, this, &GameServer::ClientDisconnected);
	connect(socket, &QTcpSocket::readyRead, this, &GameServer::ReadData);
}

void GameServer::ReadData()
{
	QTcpSocket* SenderClient = qobject_cast<QTcpSocket*>(sender());
	QThread* HandlerThread = new QThread();
	ServerRequestHandler* handler = new ServerRequestHandler(SenderClient);
	handler->moveToThread(HandlerThread);
	connect(HandlerThread, &QThread::started, handler, [handler, SenderClient]() {
		while (SenderClient->canReadLine()) {
			handler->AnalyzeResponse(SenderClient->readLine());
		}
	});
	connect(HandlerThread, &QThread::finished, handler, &QObject::deleteLater);
	connect(HandlerThread, &QThread::finished, HandlerThread, &QObject::deleteLater);
	HandlerThread->start();
}

void GameServer::ClientDisconnected() 
{
	QTcpSocket* disconnectedClient = qobject_cast<QTcpSocket*>(sender());
	for (auto const& user : ServerStorage::instance().GetOnlineUsers()) {
		if (user.GetSocket() == disconnectedClient) {
			ServerStorage::instance().UserDisconnected(user.GetUserName());
			break;
		}
	}
	_clients.removeOne(disconnectedClient);
	disconnectedClient->deleteLater();
}