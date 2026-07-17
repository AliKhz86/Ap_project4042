#include "ServerStorage.h"

ServerStorage& ServerStorage::instance()
{
	static ServerStorage StorageInstance;
	return StorageInstance;
}

void ServerStorage::AddGame(Game& newGame)
{
	static QMutex AddGameMutex;
	QMutexLocker locker(&AddGameMutex);
	RunningGames.insert(newGame.GetGameID(), newGame);
}

void ServerStorage::AddUser(User& newUser)
{
	static QMutex AddUserMutex;
	QMutexLocker locker(&AddUserMutex);
	OnlineUsers.insert(newUser.GetUserName(), newUser);
}

void ServerStorage::GameFinished(int id)
{
	static QMutex GameFinishedMutex;
	QMutexLocker locker(&GameFinishedMutex);
	RunningGames.remove(id);
}

void ServerStorage::UserDisconnected(QString Username)
{
	static QMutex UserDisconnectedMutex;
	QMutexLocker locker(&UserDisconnectedMutex);
	OnlineUsers.remove(Username);
}

const QMap<QString, User>& ServerStorage::GetOnlineUsers() const
{
	return OnlineUsers;
}

const QMap<int, Game>& ServerStorage::GetRunningGames() const
{
	return RunningGames;
}

