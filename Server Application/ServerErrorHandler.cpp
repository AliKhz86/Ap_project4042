#include "ServerErrorHandler.h"

ServerErrorHandler::ServerErrorHandler(const char* message): _message(message)
{}

const char* ServerErrorHandler::what() const noexcept
{
	return _message;
}

void ServerErrorHandler::raise() const
{
	throw* this;
}

ServerErrorHandler* ServerErrorHandler::clone() const
{
	return new ServerErrorHandler(*this);
}

void ServerErrorHandler::SendError(QTcpSocket& reciver, QString message)
{
    QJsonObject errorMessage;
    errorMessage["type"] = "ERROR";
    errorMessage["data"] = QJsonObject{
        {"message", message}
    };
    reciver.write(QJsonDocument(errorMessage).toJson(QJsonDocument::Compact).append('\n'));
    reciver.flush();
}
