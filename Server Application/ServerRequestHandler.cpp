#include "ServerRequestHandler.h"


ServerRequestHandler::ServerRequestHandler(QTcpSocket* Sender, QObject* parent) : QObject(parent) 
{
    _sender = Sender;
}

void ServerRequestHandler::AnalyzeResponse(QByteArray response)
{
    QJsonDocument ResponseDocument = QJsonDocument::fromJson(response);
    if (ResponseDocument.isNull() || ResponseDocument.isEmpty()) {
        qDebug() << "An Error to Analyze Response";
        return;
    }
    QJsonObject ResponseObject = ResponseDocument.object();
    QString type = ResponseObject["type"].toString();
    QJsonObject data = ResponseObject["data"].toObject();
    if (_Handler.contains(type)) {
        RequestHandlerFunction handler = _Handler[type];
        (this->*handler)(data);
    }
}
