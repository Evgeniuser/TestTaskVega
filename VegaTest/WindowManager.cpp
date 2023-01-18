#include "WindowManager.h"

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
}

