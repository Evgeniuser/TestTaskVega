#pragma once
#include <QMap>
#include <QString>

#include "DataTypes.h"

class DataStorage
{
public:
	DataStorage();
	~DataStorage();

	void addDevice(Device device);
	DeviceList getDevicesList() const;
	bool getDevice(const int& id, Device& device) const;
	void addStage(int id,QString name);
	bool getStage(const int& id, QString& name) const;
	QMap<int, QString> getStagesList(const int& id) const;
	DocList getDocList(const int& DeviceId, const int& StageNum) const;
	DocList getDocs() const { return m_Docs.values(); }
	void addDoc(int Id, Doc doc);
	void addDevDoc(int devId, int stageNum, QList<int> docs);
	void addDevDoc(int devId, int stageNum, int docs);
	void removeDoc(int idDev, int stageNum, int docId);
	void updateDoc(int id, Doc doc);
	int getDocId() const { return m_Docs.keys().size()+1; }
private:
	DeviceMap m_Devices;
	QMap<int, QString> m_StageName;
	DocMap m_Docs;
	DeviceStageDocConnect m_DSDC;

};

