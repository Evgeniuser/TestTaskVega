#include <QHBoxLayout>

#include "CentralWindow.h"
#include "CoreApp.h"

CentralWindow::CentralWindow(QWidget* parent)
	: QWidget(parent)
{
	m_opList = new QListView();
	m_opList->setModel(CoreApp::app()->data()->getStageModel());
	m_opFlTabs = new QTabWidget();
	m_manualList = new QListView(m_opFlTabs);
	m_manualList->setModel(CoreApp::app()->data()->getManualModel());
	m_firmwareList = new QListView(m_opFlTabs);
	m_firmwareList->setModel(CoreApp::app()->data()->getFirmwareModel());
	m_devName = new QComboBox();

	m_opFlTabs->addTab(m_manualList, QString::fromUtf8("Инструкции"));
	m_opFlTabs->addTab(m_firmwareList, QString::fromUtf8("Прошивки"));

	m_addFlButton = new QPushButton(QString::fromUtf8("Добавить файл"));
	m_editFlButton = new QPushButton(QString::fromUtf8("Редактировать файл"));
	m_removeFlButton = new QPushButton(QString::fromUtf8("Удалить файл"));

	auto buttonLayout = new QHBoxLayout(nullptr);
	buttonLayout->addWidget(m_editFlButton);
	buttonLayout->addWidget(m_addFlButton);
	buttonLayout->addWidget(m_removeFlButton);

	mainLayout = new QGridLayout(this);
	mainLayout->addWidget(m_devName, 0, 0);
	mainLayout->addWidget(m_opList, 1, 0);
	mainLayout->addWidget(m_opFlTabs, 1, 1);
	mainLayout->addLayout(buttonLayout, 2, 1, 1, 1);
	fillDevicesList();
	fillStageList();

	connect(m_devName, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CentralWindow::fillStageList);
	connect(m_opList, &QListView::clicked, this, [this](const QModelIndex& index)
		{
			auto _id = m_opList->model()->data(index, Qt::UserRole).toInt();
			CoreApp::app()->data()->updateDocModel(m_devName->currentData().toInt(), _id);
		});
	connect(m_addFlButton, &QPushButton::clicked, this, [this]()
		{
			auto devId = m_devName->currentData().toInt();
			auto docType = m_opFlTabs->currentIndex() + 1;
			auto stgNum = m_opList->model()->data(m_opList->currentIndex(), Qt::UserRole).toInt();
			CoreApp::app()->data()->addDoc(devId, stgNum, docType, "Документ ");
		});
	connect(m_removeFlButton, &QPushButton::clicked, this, [this]()
		{
			const auto devId = m_devName->currentData().toInt();
			const auto curList = qobject_cast<QListView*>(m_opFlTabs->currentWidget());
			const auto docId = curList->model()->data(curList->currentIndex(), Qt::UserRole).toInt();
			const auto stgNum = m_opList->model()->data(m_opList->currentIndex(), Qt::UserRole).toInt();
			CoreApp::app()->data()->removeDoc(devId, stgNum, docId);
			curList->setCurrentIndex(curList->model()->index(0,0));
		});
	setLayout(mainLayout);

}

CentralWindow::~CentralWindow()
{

}

void CentralWindow::fillDevicesList() const
{
	DeviceList DevLst = CoreApp::app()->data()->getDeviceList();
	for (auto& item : DevLst)
	{
		m_devName->addItem(item.name(), item.id());
	}
}

void CentralWindow::fillStageList() const
{
	CoreApp::app()->data()->fillStageModel(m_devName->currentData().toInt());
	auto _id = m_opList->model()->data(m_opList->currentIndex(), Qt::UserRole).toInt();
	CoreApp::app()->data()->updateDocModel(m_devName->currentData().toInt(), _id);
}
