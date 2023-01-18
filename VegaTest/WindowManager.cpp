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
	
	m_menuBar->addAction(QString::fromUtf8("Параметры"), this, [this]()
		{
			SettingsDialog dlg(this);
			dlg.exec();
		});
	m_menuBar->addAction(QString::fromUtf8("О Qt"),&CoreApp::aboutQt);
	m_menuBar->addAction(QString::fromUtf8("Выход"), &CoreApp::quit);
}

