#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "Tags.h"
#include "DataProcessor.h"

#include "CoreApp.h"

DataProcessor::DataProcessor()
{
}

DataProcessor::~DataProcessor()
{
	saveDocs();
	saveDDS();
}

void DataProcessor::initModels()
{
	m_StageModel = new StageModel();
	m_FirmwareModel = new StageModel();
	m_ManualModel = new StageModel();
}

bool DataProcessor::loadData()
{
	loadStagesName();
	loadDevicesList();
	loadDocs();
	loadDSDC();
	return true;
}

bool DataProcessor::loadDevicesList()
{
	const auto docJson = openFile(CoreApp::app()->deviceFilePath());
	const auto deviceFile = docJson.second.object();
	auto array = deviceFile.value(devicesTag).toArray();
	for (auto item : array)
	{
		const auto obj = item.toObject();
		auto dev = Device(obj.value(idTag).toInt(), obj.value(nameTag).toString(), obj.value(snTag).toString());
		QList<int> stgList{};
		auto arr = obj.value(stagesTag).toArray();
		for (auto stg : arr) stgList.append(stg.toInt());
		dev.addStageList(stgList);
		m_Storage.addDevice(dev);
	}
	return true;
}

bool DataProcessor::loadStagesName()
{
	const auto docJson = openFile(CoreApp::app()->stageFilePath());
	const auto map = docJson.second.object();
	for (auto key : map.keys())
	{
		const auto id = map.value(key).toInt();
		m_Storage.addStage(id, key);
	}
	return true;
}

bool DataProcessor::loadDocs()
{
	const auto docJson = openFile(CoreApp::app()->docFilePath());
	const auto docLst = docJson.second.array();
	for (auto itm : docLst)
	{
		auto docObj = itm.toObject();
		Doc doc(docObj.value(idTag).toInt(),
			docObj.value(docNameTag).toString(),
			docObj.value(docPathTag).toString(),
			docObj.value(docTypeTag).toInt());
		m_Storage.addDoc(docObj.value(idTag).toInt(), doc);
	}
	return true;
}

bool DataProcessor::loadDSDC()
{
	const auto docJson = openFile(CoreApp::app()->DDSFilePath());
	const auto docMap = docJson.second.object();
	for (auto key : docMap.keys())
	{
		auto docLst = docMap.value(key).toArray();
		QMap<int, QList<int>> ddsMap;
		for (auto itm : docLst)
		{
			QList<int> docList{};
			for (auto _doc : itm.toObject().value(docListTag).toArray()) docList.append(_doc.toInt());
			const auto stageNum = itm.toObject().value(stageTag).toInt();
			ddsMap.insert(stageNum, docList);
		}
		DDS dds(key.toInt(), ddsMap);
		m_Storage.addDevDoc(key.toInt(), dds);
	}
	return true;
}

QList<Device> DataProcessor::getDeviceList() const
{
	return m_Storage.getDevicesList();
}

Device DataProcessor::getDevice(const int& id) const
{
	Device dev{};
	m_Storage.getDevice(id, dev);
	return dev;
}

QMap<int, QString> DataProcessor::getStageList(const int& id) const
{
	return m_Storage.getStagesList(id);
}

void DataProcessor::updateStageModel(const int& devId) const
{
	m_StageModel->clear();
	auto lst = getStageList(devId);
	for (auto itm : lst.keys())
	{
		m_StageModel->addValue(lst.value(itm), itm);
	}
}

void DataProcessor::updateDocModel(const int& devId, const int& stageNum) const
{
	m_FirmwareModel->clear();
	m_ManualModel->clear();
	auto lst = m_Storage.getDocList(devId, stageNum);
	for (auto itm : lst)
	{
		if (itm.docType() == 1)
			m_ManualModel->addValue(itm.name(), itm.id());
		else if (itm.docType() == 2)
			m_FirmwareModel->addValue(itm.name(), itm.id());
	}

}

void DataProcessor::addDoc(int devId, int stageNum, int docType, QString docName, QString docPath)
{
	Doc _doc = Doc(m_Storage.getDocId(), docName, docPath, docType);
	m_Storage.addDoc(_doc.id(), _doc);
	m_Storage.addDevDoc(devId, stageNum, _doc.id());
	updateDocModel(devId, stageNum);
}

void DataProcessor::removeDoc(int idDev, int stageNum, int docId)
{
	m_Storage.removeDoc(idDev, stageNum, docId);
	updateDocModel(idDev, stageNum);
}

void DataProcessor::editDoc(int devId, int stageNum, int docId, QString docName, QString filePath)
{
	m_Storage.updateDoc(docId, docName, filePath);
	updateDocModel(devId, stageNum);
	
}

void DataProcessor::getDocInfo(const int& id, QString& docName, QString& filePath) const
{
	m_Storage.getDocInfo(id, docName, filePath);
}

QPair<QJsonParseError, QJsonDocument> DataProcessor::openFile(const QString& fileName) const
{
	if (QFile::exists(fileName))
	{
		QFile File(fileName);
		File.open(QIODevice::ReadOnly);
		const QByteArray Data = File.readAll();
		File.close();
		QJsonParseError error{};
		QJsonDocument doc(QJsonDocument::fromJson(Data, &error));
		return QPair<QJsonParseError, QJsonDocument>{error, doc};
	}
	return QPair<QJsonParseError, QJsonDocument>{QJsonParseError{}, QJsonDocument{}};
}

bool DataProcessor::saveDocs() const
{
	QFile File(CoreApp::app()->docFilePath());
	File.open(QIODevice::WriteOnly);
	QJsonArray arr;
	for (auto& itm : m_Storage.getDocs()) arr.append(itm.toJson());
	QJsonDocument doc;
	doc.setArray(arr);
	File.write(doc.toJson());
	File.close();
	return true;
}

bool DataProcessor::saveDDS() const
{
	QFile File(CoreApp::app()->DDSFilePath());
	File.open(QIODevice::ReadWrite);
	QJsonObject obj;
	for(auto itm : m_Storage.getDDSList())
	{
		obj.insert(QString::number(itm.getDevId()), itm.toJson());
	}
	QJsonDocument doc;
	doc.setObject(obj);
	File.write(doc.toJson());
	File.close();
	return true;
}
