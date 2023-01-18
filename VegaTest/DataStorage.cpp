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
	auto lst = m_DSDC.value(DeviceId).value(StageNum);
	DocList docLst{};
	for (auto id : lst) docLst.append(m_Docs.value(id));
	return docLst;
}

void DataStorage::addDoc(int Id, Doc doc)
{
	m_Docs.insert(Id, doc);
}

void DataStorage::addDevDoc(int devId, int stageNum, QList<int> docs)
{
	auto stMap = m_DSDC.value(devId);
	stMap.insert(stageNum, docs);
	m_DSDC.insert(devId, stMap);
}

void DataStorage::addDevDoc(int devId, int stageNum, int docs)
{
	auto stMap = m_DSDC.value(devId);
	auto lst = stMap.value(stageNum);
	lst.append(docs);
	stMap.insert(stageNum, lst);
	m_DSDC.insert(devId, stMap);
}

void DataStorage::removeDoc(int devId, int stageNum, int docId)
{
	m_Docs.remove(docId);
	auto stMap = m_DSDC.value(devId);
	auto docLst = stMap.value(stageNum);
	docLst.removeOne(docId);
	stMap[stageNum] = docLst;
	m_DSDC[devId] = stMap;
}

void DataStorage::updateDoc(int id, Doc doc)
{
	m_Docs[id] = doc;
}
