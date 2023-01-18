#include "DataStorage.h"

DataStorage::DataStorage()
{
}

DataStorage::~DataStorage()
{
}

void DataStorage::addDevice(Device device)
{
	m_Devices.insert(device.id(), device);
}

void DataStorage::addStage(const int id, const QString name)
{
	m_StageName.insert(id, name);
}

bool DataStorage::getStage(const int& id, QString& name) const
{
	name.clear();
	name = m_StageName.value(id);
	return !name.isEmpty();
}

DeviceList DataStorage::getDevicesList() const
{
	return m_Devices.values();
}

bool DataStorage::getDevice(const int& id, Device& device) const
{
	if (m_Devices.contains(id))
	{
		device = m_Devices.value(id);
		return true;
	}
	return false;
}

QMap<int, QString> DataStorage::getStagesList(const int& id) const
{
	auto lst = m_Devices.value(id).getStageList();
	QMap<int, QString> _stagesList;
	for (auto itm : lst)
		_stagesList.insert(itm,m_StageName.value(itm));
	return _stagesList;
}

DocList DataStorage::getDocList(const int& DeviceId, const int& StageNum) const
{
	auto docIdLst = m_DSDC.value(DeviceId).getDocIdList(StageNum);
	DocList docLst{};
	for (auto id : docIdLst) docLst.append(m_Docs.value(id));
	return docLst;
}

void DataStorage::addDoc(int Id, Doc doc)
{
	m_Docs.insert(Id, doc);
	updateFreeId();
}

void DataStorage::addDevDoc(int devId, DDS dds)
{
	m_DSDC.insert(devId, dds);
}

void DataStorage::addDevDoc(int devId, int stageNum, int docs)
{
	auto dsdc = m_DSDC.value(devId);
	dsdc.addDoc(stageNum, docs);
	m_DSDC.insert(devId, dsdc);
}

void DataStorage::removeDoc(int devId, int stageNum, int docId)
{
	m_Docs.remove(docId);
	auto dsdc = m_DSDC.value(devId);
	dsdc.removeDoc(stageNum,docId);
	m_DSDC.insert(devId, dsdc);
	updateFreeId();
}

void DataStorage::updateDoc(int id, Doc doc)
{
	m_Docs.insert(id,doc);
}

void DataStorage::updateDoc(int id, QString docName, QString filePath)
{
	auto doc = m_Docs.value(id);
	doc.updateData(docName, filePath);
	m_Docs.insert(id, doc);
}

void DataStorage::getDocInfo(const int& id, QString& docName, QString& filePath) const
{
	const auto doc = m_Docs.value(id);
	docName = doc.name();
	filePath = doc.filePath();
}
