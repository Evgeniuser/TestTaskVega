#include "StageModel.h"

StageModel::StageModel(QObject* parent) : QAbstractItemModel(parent)
{

}

QModelIndex StageModel::index(int row, int column, const QModelIndex& parent) const
{
    Q_UNUSED(parent)
	return m_data.isEmpty() ? QModelIndex() : createIndex(row, column, (void*)&m_data[row]);
}

QModelIndex StageModel::parent(const QModelIndex& child) const
{
    Q_UNUSED(child)
	return {};
}

int StageModel::rowCount(const QModelIndex&) const
{
	return m_data.size();
}

int StageModel::columnCount(const QModelIndex&) const
{
	return 1;
}

QVariant StageModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid()) return {};
	switch (role)
	{
	case Qt::DisplayRole:
		return m_data.at(index.row());
	case Qt::UserRole:
		return m_id.value(m_data.at(index.row()));
	default:
		return {};
	}
}

void StageModel::addValue(const QString& value, const int id = 0)
{
	beginInsertRows(QModelIndex(),m_data.count(),m_data.count());
	m_data.append(value);
	m_id.insert(value, id);
	endInsertRows();
}

void StageModel::clear()
{
	beginResetModel();
	m_data.clear();
	endResetModel();
}

