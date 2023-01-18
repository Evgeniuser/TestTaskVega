#pragma once
#include <QAbstractItemModel>
#include <QList>
class StageModel :
    public QAbstractItemModel
{
	Q_OBJECT

public:
	StageModel(QObject* parent = nullptr);
	~StageModel() override {}

	QModelIndex index(int row, int column, const QModelIndex& parent) const override;
	QModelIndex parent(const QModelIndex& child) const override;
	int rowCount(const QModelIndex& parent) const override;
	int columnCount(const QModelIndex& parent) const override;
	QVariant data(const QModelIndex& index, int role) const override;
	void clear();

public slots:
	void addValue(const QString& value,const int id);

private:
    QList<QString> m_data{};
	QMap<QString, int> m_id;

};

