#pragma once
#include <qexception.h>
#include <qtcpsocket.h>
#include <QJsonObject>

class ServerErrorHandler : public QException {
	
private:
	const char* _message;

public:
	ServerErrorHandler(const char* message);
	const char* what() const noexcept override;
	void raise() const override;
	ServerErrorHandler* clone() const override;
	static void SendError(QTcpSocket& reciver, QString message);
};