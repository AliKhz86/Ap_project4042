#pragma once
#include <qobject.h>
#include <qjsonobject.h>
#include <qtcpsocket.h>
#include <qtcpserver.h>
#include "ServerErrorHandler.h" //Error Handling

enum class GameStatus {
	Playing,
	Suspend,
	Waiting,
	Finished
};

class Game : public QObject {
	Q_OBJECT
	typedef void (Game::* HandlerFunction)(const QJsonObject&);
private:
	QMap<QString, HandlerFunction> _ResponseHandler;

protected:
	QString _hostPlayer;
	int _hostScore;
	QString _guestPlayer;
	int _guestScore;
	GameStatus _state;
	int _serverPort;
	QTcpServer* _intenalGameServer;
	QTcpSocket* _hostSocket;
	QTcpSocket* _guestSocket;

public:
	Game(QString hostUserName, int port, QObject* parent = nullptr);
	virtual ~Game();
	static bool IsPortAvailable(int port);
	GameStatus GetGameState() const;
	virtual void SetupGameLogic(const QJsonObject& setting) = 0;
	virtual void Move(const QJsonObject& move) = 0;
	bool InitializingRoom();

signals:
	void GameOver(Game* currentGame);

private slots:
	void OnPlayerConnected();
	void OnReadyRead();
	void OnPlayerDisconnect();

protected:
	void EnterHandler(const QString& type, HandlerFunction value);

};