#pragma once
#include <qexception.h>

class ServerErrorHandler : public QException {
	
private:
	const char* _message;

public:
	ServerErrorHandler(const char* message);
	const char* what() const noexcept override;
	void raise() const override;
	ServerErrorHandler* clone() const override;
};