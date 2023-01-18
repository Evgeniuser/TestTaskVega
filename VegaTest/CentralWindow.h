#pragma once

#include <QWidget>
#include <QListWidget>
#include <QTabWidget>
#include <QComboBox>
#include <QLayout>
#include <QPushButton>



class CentralWindow  : public QWidget
{
	Q_OBJECT

public:
	CentralWindow(QWidget* parent = nullptr);
	~CentralWindow();

public slots:
	void fillStageList() const;
private:

	void fillDevicesList() const;
	QGridLayout* mainLayout;
	QListView* m_opList;
	QListView* m_manualList;
	QListView* m_firmwareList;
	QComboBox* m_devName;
	QTabWidget* m_opFlTabs;

	QPushButton* m_addFlButton;
	QPushButton* m_removeFlButton;
	QPushButton* m_editFlButton;

};
