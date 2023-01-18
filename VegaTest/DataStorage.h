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
	void addStage(int id, QString name);
	bool getStage(const int& id, QString& name) const;
	QMap<int, QString> getStagesList(const int& id) const;
	DocList getDocList(const int& DeviceId, const int& StageNum) const;
	DocList getDocs() const { return m_Docs.values(); }
	QList<DDS> getDDSList() const { return m_DSDC.values(); }
	void addDoc(int Id, Doc doc);
	void addDevDoc(int devId, DDS dds);
	void addDevDoc(int devId, int stageNum, int docs);
	void removeDoc(int idDev, int stageNum, int docId);
	void updateDoc(int id, Doc doc);
	void updateDoc(int id, QString docName, QString filePath);
	void getDocInfo(const int& id, QString& docName, QString& filePath) const;
	int getDocId() const { return m_freeId; }
private:
	DeviceMap m_Devices;
	QMap<int, QString> m_StageName;
	DocMap m_Docs;
	DeviceStageDocConnect m_DSDC;

	int m_freeId = 0;
	void updateFreeId()
	{
		m_freeId = 0;
		for (const auto& key : m_Docs.keys())
			if (m_freeId == key) m_freeId++;
			else break;
	}
};

