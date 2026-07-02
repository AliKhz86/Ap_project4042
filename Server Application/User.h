#pragma once
#include <qobject.h>
#include <qfile.h>
#include <qtcpsocket.h>
#include "ServerErrorHandler.h"

struct Record {
	QString name;
	QString userName;
	QString password;
	QString phoneNumber;
	QString emailAddress;
};

class User : public QObject {
	Q_OBJECT

private:
	QString _name;
	QString _userName;
	QString _password;
	QString _phoneNumber;
	QString _emailAddress;
	QTcpSocket* _socket;

public:
	//Also can Added "explicit" key word
	User(QTcpSocket* soket, QObject* parent = nullptr);
	static bool LoadUser(QString username, QString password);
	void SignUp(QString name, QString username, QString password, QString phone, QString email);
	void Login(QString username);
	QString GetName() const;
	QString GetUserName() const;
	QString GetPassword() const;
	QString GetPhoneNumber() const;
	QString GetEmailAdderss() const;
	QTcpSocket* GetSocket() const;
	void UpdateName(QString name);
	bool UpdateUserName(QString username);
	void UpdatePassword(QString password);
	bool UpdatePhoneNumber(QString phone);
	void UpdateEmailAdderss(QString email);

private:
	static QVector<Record> _getAllUserInformation();
	void _writeAllUserInformation(QVector<Record> Users) const;
};