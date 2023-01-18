#pragma once
#include <QJsonArray>
#include <QJsonObject>
#include <QMap>
#include <QList>
#include <QString>

#include "Tags.h"

struct Base
{
public:
	Base() = default;
	Base(QString name, const int id) : m_Name(name), m_Id(id) {}
	const QString& name() const { return m_Name; }
	Base(const Base& other) = default;
	Base& operator=(const Base& other)
	{
		if (this == &other)
			return *this;
		m_Name = other.m_Name;
		m_Id = other.m_Id;
		return *this;
	}
	const int& id() const { return m_Id; }
	bool isEmpty() const { return m_Id == -1; }
private:
	QString m_Name{};
	int m_Id = -1;
};

struct Device : Base
{
public:
	Device() : Base(), m_SerialNumber(QString()) {}
	Device(int id, QString name, QString serialNumber) : Base(name, id), m_SerialNumber(serialNumber) {}
	Device(const Device& other) = default;
	Device& operator=(const Device& other)
	{
		if (this == &other)
			return *this;
		Base::operator =(other);
		m_SerialNumber = other.m_SerialNumber;
		m_StageList = other.m_StageList;
		return *this;
	}
	const QString& serialNumber() const { return m_SerialNumber; }
	void addStageList(const QList<int>& stages) { m_StageList.clear();  m_StageList.append(stages); }
	QList<int> getStageList() const { return m_StageList; }
	QJsonObject toJson() const
	{
		QJsonObject Object;
		Object.insert(idTag, QJsonValue(id()));
		Object.insert(nameTag, QJsonValue(name()));
		Object.insert(snTag, QJsonValue(serialNumber()));
		QJsonArray stg;
		for (const auto itm : getStageList()) stg.append(QJsonValue(itm));
		Object.insert(stagesTag, stg);
		return Object;
	}
private:
    QString m_SerialNumber{};
    QList<int> m_StageList{};
};

struct Doc : Base
{
public:
	Doc() :Base(), m_FilePath(QString()), m_DocType(-1) {}
	Doc(int id, QString name, QString fileName, int docType) : Base(name, id), m_FilePath(fileName), m_DocType(docType) {}
	const QString& filePath() const { return m_FilePath; }
	const int& docType() const { return m_DocType; }
	void setFilePath(const QString filePath) { m_FilePath = filePath; }
	void setDocType(const int docType) { m_DocType = docType; }
	QJsonObject toJson() const
	{
		QJsonObject Object;
		Object.insert(idTag, QJsonValue(id()));
		Object.insert(nameTag, QJsonValue(name()));
		Object.insert(docPathTag, QJsonValue(filePath()));
		Object.insert(docTypeTag, QJsonValue(docType()));
		return Object;
	}
private:
	QString m_FilePath;
	int m_DocType;
};

struct DDS
{
public:
	DDS(const int devId, const QMap<int, QList<int>> stgDocList) : m_devId(devId), m_stgDocList(stgDocList){}
	QList<int> getDocList(const int stageId) const { return m_stgDocList.value(stageId); }
	void addDoc(const int stageId, const int docId) { }
	QJsonObject toJson() const
	{
		QJsonObject obj;
		QJsonArray arr;
		for(auto key : m_stgDocList.keys())
		{
			QJsonObject stgObj;
			QJsonArray docArr;
			stgObj.insert(stageTag, key);
			for (auto itm : m_stgDocList.value(key)) docArr.append(QJsonValue(itm));
			stgObj.insert(docListTag, QJsonValue(docArr));
			arr.append(QJsonValue(stgObj));
		}
		obj.insert(QString::number(devId()), QJsonValue(arr));

		return obj;
	}
private:
	int devId() const { return m_devId; }

	int m_devId;
	QMap<int, QList<int>> m_stgDocList{};
};

typedef int Id;
typedef QMap<Id, Device> DeviceMap;
typedef QList<Device> DeviceList;
typedef QMap<Id, Doc> DocMap;
typedef QList<Doc> DocList;
typedef int DeviceId;
typedef int StageNum;
typedef QMap<DeviceId, QMap<StageNum,QList<int>>> DeviceStageDocConnect;
