#pragma once
#include <qobject.h>
#include <qjsonobject.h>
#include <qdebug.h>
#include <qtcpsocket.h>
#include "ServerStorage.h"
#include "ServerErrorHandler.h"

class ServerRequestHandler : public QObject {
	Q_OBJECT
	typedef void (ServerRequestHandler::*RequestHandlerFunction)(const QJsonObject& data);
private:
	QMap<QString, RequestHandlerFunction> _Handler = {
		
	};
	
	QTcpSocket* _sender;

public:
	ServerRequestHandler(QTcpSocket* Sender, QObject* parent = nullptr);

public slots:
	void AnalyzeResponse(QByteArray response);

/*
* Functions are created to handle requests sent to the server,
*	which have the same signature as RequestHandlerFunction and are stored in the _Handler QMap.
*/
private:

};