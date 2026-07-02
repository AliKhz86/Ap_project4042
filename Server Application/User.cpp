#include "User.h"

User::User(QTcpSocket* soket, QObject* parent): QObject(parent)
{
	_socket = soket;
}

bool User::LoadUser(QString username, QString password)
{
	QVector<Record> Input = _getAllUserInformation();
	for (const Record& user : Input) {
		if (user.userName == username) {
			if (user.password == password)
				return true;
			else
				return false;
		}
	}
	return false;
}

void User::SignUp(QString name, QString username, QString password, QString phone, QString email)
{
	QVector<Record> Input = _getAllUserInformation();
	for (const Record& user : Input) {
		if (user.userName == username)
			throw ServerErrorHandler("This username has already been chosen by someone else");
		if(user.phoneNumber == phone)
			throw ServerErrorHandler("This phone number is already registered in the game");
	}
	_name = name;
	_userName = username;
	_password = password;
	_phoneNumber = phone;
	_emailAddress = email;
	QFile file("Users.bin");
	file.open(QIODevice::WriteOnly | QIODevice::Append);
	QDataStream Output(&file);
	Output.setVersion(6);
	Output << name << username << password << phone << email;
	file.close();
}

void User::Login(QString username)
{
	QVector<Record> Input = _getAllUserInformation();
	for (const Record& user : Input) {
		if (user.userName == username) {
			_name = user.name;
			_userName = user.userName;
			_password = user.password;
			_phoneNumber = user.phoneNumber;
			_emailAddress = user.emailAddress;
			return;
		}
	}
}

QString User::GetName() const
{
	return _name;
}

QString User::GetUserName() const
{
	return _userName;
}

QString User::GetPassword() const
{
	return _password;
}

QString User::GetPhoneNumber() const
{
	return _phoneNumber;
}

QString User::GetEmailAdderss() const
{
	return _emailAddress;
}

QTcpSocket* User::GetSocket() const
{
	return _socket;
}

void User::UpdateName(QString name)
{
	QVector<Record> Input = _getAllUserInformation();
	for (Record& user : Input) {
		if (user.name == _name) {
			user.name = name;
			_name = name;
			break;
		}
	}
	_writeAllUserInformation(Input);
}

bool User::UpdateUserName(QString username)
{
	QVector<Record> Input = _getAllUserInformation();
	for (Record& user : Input) {
		if (user.userName == username) {
			return false;
		}
	}
	for (Record& user : Input) {
		if (user.userName == _userName) {
			user.userName = username;
			_userName = username;
			break;
		}
	}
	_writeAllUserInformation(Input);
	return true;
}

void User::UpdatePassword(QString password)
{
	QVector<Record> Input = _getAllUserInformation();
	for (Record& user : Input) {
		if (user.password == _password) {
			user.password = password;
			_password = password;
			break;
		}
	}
	_writeAllUserInformation(Input);
}

bool User::UpdatePhoneNumber(QString phone)
{
	QVector<Record> Input = _getAllUserInformation();
	for (Record& user : Input) {
		if (user.phoneNumber == phone) {
			return false;
		}
	}
	for (Record& user : Input) {
		if (user.phoneNumber == _phoneNumber) {
			user.phoneNumber = phone;
			_phoneNumber = phone;
			break;
		}
	}
	_writeAllUserInformation(Input);
	return true;
}

void User::UpdateEmailAdderss(QString email)
{
	QVector<Record> Input = _getAllUserInformation();
	for (Record& user : Input) {
		if (user.emailAddress == _emailAddress) {
			user.emailAddress = email;
			_emailAddress = email;
			break;
		}
	}
	_writeAllUserInformation(Input);
}


QVector<Record> User::_getAllUserInformation()
{
	QFile file("Users.bin");
	if (file.exists() == false)
		return QVector<Record>();
	file.open(QIODeviceBase::ReadOnly);
	QDataStream Input(&file);
	Input.setVersion(6);
	QVector<Record> AllUser;
	while (Input.atEnd() == false) {
		Record user;
		Input >> user.name >> user.userName >> user.password >> user.phoneNumber >> user.emailAddress;
		AllUser.push_back(user);
	}
	file.close();
	return AllUser;
}

void User::_writeAllUserInformation(QVector<Record> Users) const
{
	QFile file("Users.bin");
	file.open(QIODeviceBase::WriteOnly);
	QDataStream Output(&file);
	Output.setVersion(6);
	for (const Record& user : Users) {
		Output << user.name << user.userName << user.password << user.phoneNumber << user.emailAddress;
	}
	file.close();
}
