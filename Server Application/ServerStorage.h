#pragma once
#include <qobject.h>
#include <qmutex.h>
#include "User.h"
#include "Game.h"
/*
* The following resources were used to write the code for this section:
*	1. https://www.geeksforgeeks.org/cpp/creational-pattern-in-c/ ===> https://www.geeksforgeeks.org/system-design/singleton-pattern-c-design-patterns/
*	2. https://refactoring.guru/design-patterns/singleton
*	3. https://stackoverflow.com/questions/86582/singleton-how-should-it-be-used
*	4. https://en.cppreference.com/cpp/language/default_constructor ===> https://stackoverflow.com/questions/20828907/the-new-syntax-default-in-c11
*	5. https://stackoverflow.com/questions/69205644/how-to-prevent-the-creation-of-an-object-in-c
*/


class ServerStorage : public QObject {
	Q_OBJECT

private:
	ServerStorage() = default;
	QMap<QString, User> OnlineUsers;
	QMap<int, Game> RunningGames;

public:
	ServerStorage(const ServerStorage& cpy) = delete;
	ServerStorage& operator=(const ServerStorage& rop) = delete;
	static ServerStorage& instance();

	void AddGame(Game& newGame);
	void AddUser(User& newUser);
	void GameFinished(int id);
	void UserDisconnected(QString Username);
	
	const QMap<QString, User>& GetOnlineUsers() const;
	const QMap<int, Game>& GetRunningGames() const;

};