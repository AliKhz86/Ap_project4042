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
