#include "WindowManager.h"
#include "SettingsDialog.h"
#include "CoreApp.h"

class CoreApp;

WindowManager::WindowManager(QWidget *parent)
	: QMainWindow(parent)
{
	setObjectName("MainWindow");
	m_centralWindow = new CentralWindow(this);
	m_menuBar = new QMenuBar(this);
	CreateMenu();
	setMenuBar(m_menuBar);
	setCentralWidget(m_centralWindow);
	CoreApp::readParam(this);
}

WindowManager::~WindowManager()
{
	CoreApp::writeParam(this);
	delete m_menuBar;
	delete m_statusBar;
	delete m_centralWindow;
}

void WindowManager::CreateMenu()
{
	
	auto settingAct = new QAction(QString::fromUtf8("Параметры"), this);
	connect(settingAct, &QAction::triggered, this, [this]()
		{
			SettingsDialog dlg(this);
	dlg.exec();
		});
	m_menuBar->addAction(settingAct);
	auto aboutAct = new QAction(QString::fromUtf8("О Qt"), this);
	connect(aboutAct, &QAction::triggered, this, &CoreApp::aboutQt);
	m_menuBar->addAction(aboutAct);

}

