#pragma once
#include <QString>

class ConnectionManager
{
public:
	ConnectionManager();
	~ConnectionManager();
private:

	QString m_DataBaseName;
	QString m_DriverName;
};

