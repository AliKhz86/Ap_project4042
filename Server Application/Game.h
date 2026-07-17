#pragma once
#include <functional> //resource: https://www.geeksforgeeks.org/cpp/std-function-in-cpp/
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

struct ReturnNode {
	QString GameName;
	int GameID;
	QString HostName;
	int HostScore;
	QString GuestName;
	int GuestScore;
};

class Game : public QObject {
	Q_OBJECT
	typedef std::function<void(const QJsonObject&)> HandlerFunction;
private:
	QMap<QString, HandlerFunction> _ResponseHandler;
	static int _Counter;

protected:
	const int _gameID;
	const QString _gameName;
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
	Game(QString gameName, QString hostUserName, int port, QObject* parent = nullptr);
	virtual ~Game();
	static bool IsPortAvailable(int port);
	GameStatus GetGameState() const;
	virtual void SetupGameLogic(const QJsonObject& setting) = 0;
	virtual void Move(const QJsonObject& move) = 0;
	virtual void SaveGame() = 0;
	virtual QVector<ReturnNode> LoadGames() = 0;
	bool InitializingRoom();
	int GetGameID() const;


signals:
	void GameOver(Game* currentGame);

private slots:
	void OnPlayerConnected();
	void OnReadyRead();
	void OnPlayerDisconnect();

protected:
	template<typename T>
	void AddHandler(const QString& type, T* GameChild, void (T::*ChildHandler)(const QJsonObject&));

};

template<typename T>
inline void Game::AddHandler(const QString& type, T* GameChild, void(T::* ChildHandler)(const QJsonObject&))
{
	_ResponseHandler[type] = [=](const QJsonObject& data) {
		(GameChild->*ChildHandler)(data);
	};
	/*
	* Resource for this Code:
	* https://medium.com/@sgn00/diving-into-std-function-d342e4b58ea7
	* https://www.geeksforgeeks.org/cpp/lambda-expression-in-c/
	* https://www.geeksforgeeks.org/cpp/lambda-capture-clause-in-cpp/
	*/
}
