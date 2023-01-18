#include <QHBoxLayout>
#include <QMessageBox>

#include "CentralWindow.h"
#include "CoreApp.h"
#include "FileDialog.h"

CentralWindow::CentralWindow(QWidget* parent)
	: QWidget(parent)
{
	m_opList = new QListView(this);
	m_opList->setModel(CoreApp::app()->data()->getStageModel());
	m_opFlTabs = new QTabWidget(this);
	m_manualList = new QListView(m_opFlTabs);
	m_manualList->setModel(CoreApp::app()->data()->getManualModel());
	m_firmwareList = new QListView(m_opFlTabs);
	m_firmwareList->setModel(CoreApp::app()->data()->getFirmwareModel());
	m_devName = new QComboBox(this);

	m_opFlTabs->addTab(m_manualList, QString::fromUtf8("Инструкции"));
	m_opFlTabs->addTab(m_firmwareList, QString::fromUtf8("Прошивки"));

	m_addFlButton = new QPushButton(QString::fromUtf8("Добавить файл"), this);
	m_editFlButton = new QPushButton(QString::fromUtf8("Редактировать файл"), this);
	m_removeFlButton = new QPushButton(QString::fromUtf8("Удалить файл"), this);

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
			FileDialog dlg(QString::fromUtf8("Добавить файл"), m_devName->currentText(),
		m_opList->model()->data(m_opList->currentIndex()).toString(), this);
			dlg.setModal(true);
			if (dlg.exec() == QDialog::Accepted)
			{
				auto lst = dlg.getData();
				CoreApp::app()->data()->addDoc(devId, stgNum, docType, lst.last().toString(), lst.first().toString());
			}
		});
	connect(m_removeFlButton, &QPushButton::clicked, this, [this]()
		{
			const auto curList = qobject_cast<QListView*>(m_opFlTabs->currentWidget());
			if(curList->currentIndex().isValid())
			{
				const auto devId = m_devName->currentData().toInt();
				const auto docId = curList->model()->data(curList->currentIndex(), Qt::UserRole).toInt();
				const auto stgNum = m_opList->model()->data(m_opList->currentIndex(), Qt::UserRole).toInt();
				CoreApp::app()->data()->removeDoc(devId, stgNum, docId);
				curList->setCurrentIndex(curList->model()->index(0, 0));
			}
			else
			{
				QMessageBox::warning(this, QString::fromUtf8("Внимание"), QString::fromUtf8("Файл не выбран или список пуст"));
			}
		});
	connect(m_editFlButton, &QPushButton::clicked, this, [this]()
		{
			
			const auto curList = qobject_cast<QListView*>(m_opFlTabs->currentWidget());
			if(curList->currentIndex().isValid())
			{
				QString docName, filePath;
			   const auto docId = curList->model()->data(curList->currentIndex(), Qt::UserRole).toInt();
			   CoreApp::app()->data()->getDocInfo(docId, docName, filePath);
			   FileDialog dlg(QString::fromUtf8("Редактировать файл"), m_devName->currentText(),
			   m_opList->model()->data(m_opList->currentIndex()).toString(),docName,filePath, this);
			   dlg.setModal(true);
			   if (dlg.exec() == QDialog::Accepted)
			   {
				   const auto devId = m_devName->currentData().toInt();
				   const auto stgNum = m_opList->model()->data(m_opList->currentIndex(), Qt::UserRole).toInt();
				   auto lst = dlg.getData();
				   CoreApp::app()->data()->editDoc(devId,stgNum,docId, lst.last().toString(), lst.first().toString());
			   }
			}
			else
			{
				QMessageBox::warning(this, QString::fromUtf8("Внимание"), QString::fromUtf8("Файл не выбран или список пуст"));
			}
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
	if (!m_opList->currentIndex().isValid())
		m_opList->setCurrentIndex(m_opList->model()->index(0, 0));	
	auto _id = m_opList->model()->data(m_opList->currentIndex(), Qt::UserRole).toInt();	
	CoreApp::app()->data()->updateDocModel(m_devName->currentData().toInt(), _id);
}
