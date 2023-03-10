#pragma once
#include <QVariant>
#include <QJsonParseError>

#include "DataStorage.h"
#include "StageModel.h"

class CoreApp;

class DataProcessor
{
public:
	DataProcessor();
	~DataProcessor();

	bool loadData();
	void initModels();
	void updateStageModel(const int& devId) const;
	void updateDocModel(const int& devId, const int& stageNum) const;

	void addDoc(int devId, int stageNum, int typeDoc, QString docName, QString docPath);
	void editDoc(int devId, int stageNum, int docId, QString docName, QString filePath);
	void removeDoc(int idDev, int stageNum, int docId);
	void getDocInfo(const int& id, QString& docName, QString& filePath) const;
	StageModel* getStageModel() const { return m_StageModel; }
	StageModel* getManualModel() const { return m_ManualModel; }
	StageModel* getFirmwareModel() const { return m_FirmwareModel; }
	QList<Device> getDeviceList() const;

private:
	bool loadDevicesList();
	bool loadStagesName();
	bool loadDocs();
	bool loadDSDC();

	bool saveDocs() const;
	bool saveDDS() const;
	Device getDevice(const int& id) const;
	QMap<int, QString> getStageList(const int& id) const;

	DataStorage m_Storage;
	StageModel* m_StageModel;
	StageModel* m_ManualModel;
	StageModel* m_FirmwareModel;
	QPair<QJsonParseError, QJsonDocument> openFile(const QString& fileName) const;
};

