#include "Game.h"

Game::Game(QString gameName, QString hostUserName, int port, QObject* parent): QObject(parent), _gameID(_Counter), _gameName(gameName)
{
    _hostPlayer = hostUserName;
    _hostScore = 0;
    _guestScore = 0;
    _state = GameStatus::Waiting;
    _serverPort = port;
    _intenalGameServer = nullptr;
    _hostSocket = nullptr;
    _guestSocket = nullptr;
    AddHandler<Game>("MOVE", this, &Game::Move);
    AddHandler<Game>("SETUP", this, &Game::SetupGameLogic);
    ++_Counter;
}

Game::~Game()
{
    if (_hostSocket)
        _hostSocket->close();
    if (_guestSocket)
        _guestSocket->close();
    if (_intenalGameServer)
        _intenalGameServer->close();
}

bool Game::IsPortAvailable(int port)
{
    QTcpServer TestPort;
    if (TestPort.listen(QHostAddress::Any, port) == true) {
        TestPort.close();
        return true;
    }
    return false;
}

GameStatus Game::GetGameState() const
{
    return _state;
}

bool Game::InitializingRoom()
{
    _intenalGameServer = new QTcpServer();
    _intenalGameServer->setParent(this);
    if (_intenalGameServer->listen(QHostAddress::Any, _serverPort) == false) {
        delete _intenalGameServer;
        return false;
    }
    connect(_intenalGameServer, &QTcpServer::newConnection, this, &Game::OnPlayerConnected);
    return true;
}

void Game::OnReadyRead()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (socket == nullptr)
        return;
    QJsonDocument ResponseDocument = QJsonDocument::fromJson(socket->readAll());
    if (ResponseDocument.isNull() || ResponseDocument.isEmpty()) {
        qDebug() << "An Error to Analyze Response in Game File";
        return;
    }
    QJsonObject ResponseObject = ResponseDocument.object();
    QString type = ResponseObject["type"].toString();
    QJsonObject data = ResponseObject["data"].toObject();
    if (_ResponseHandler.contains(type)) {
        _ResponseHandler[type](data);
    }
}

void Game::OnPlayerDisconnect()
{
    QTcpSocket* disconectedSocket = qobject_cast<QTcpSocket*>(sender());
    if (disconectedSocket == nullptr)
        return;
    _state = GameStatus::Suspend;
    if (disconectedSocket == _hostSocket) {
        if (_guestSocket != nullptr && _guestSocket->state() == QTcpSocket::ConnectingState) {
            QJsonObject errorMessage;
            errorMessage["type"] = "NOTIFY";
            errorMessage["data"] = QJsonObject{
                {"message", "PLAYER_DISCONNECTED_NOTIFY"}
            };
            _guestSocket->write(QJsonDocument(errorMessage).toJson(QJsonDocument::Compact).append('\n'));
            _guestSocket->flush();
        }
    }
    else if (disconectedSocket == _guestSocket) {
        if (_hostSocket != nullptr && _hostSocket->state() == QTcpSocket::ConnectingState) {
            QJsonObject errorMessage;
            errorMessage["type"] = "NOTIFY";
            errorMessage["data"] = QJsonObject{
                {"message", "PLAYER_DISCONNECTED_NOTIFY"}
            };
            _hostSocket->write(QJsonDocument(errorMessage).toJson(QJsonDocument::Compact).append('\n'));
            _hostSocket->flush();
        }
    }
}

void Game::OnPlayerConnected() {
    if (_hostSocket == nullptr) {
        _hostSocket = _intenalGameServer->nextPendingConnection();
        connect(_hostSocket, &QTcpSocket::readyRead, this, &Game::OnReadyRead);
        connect(_hostSocket, &QTcpSocket::disconnected, this, &Game::OnPlayerDisconnect);
        return;
    }
    if (_guestSocket == nullptr) {
        _guestSocket = _intenalGameServer->nextPendingConnection();
        connect(_guestSocket, &QTcpSocket::readyRead, this, &Game::OnReadyRead);
        connect(_guestSocket, &QTcpSocket::disconnected, this, &Game::OnPlayerDisconnect);
        _state = GameStatus::Playing;
    }
    QTcpSocket* client = _intenalGameServer->nextPendingConnection();
    QJsonObject errorMessage;
    ServerErrorHandler::SendError(*client, "You are not allowed to enter the game");
    client->disconnectFromHost();

}
