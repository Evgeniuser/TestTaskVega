#include <QSettings>

#include "CoreApp.h"

CoreApp* CoreApp::m_app = nullptr;

CoreApp::CoreApp(int& argc, char** argv) : QApplication(argc, argv)
{
	if (m_app == nullptr)
		m_app = this;
}

CoreApp::~CoreApp()
{
	saveParam();
	delete m_mainWindow;
	delete m_dataController;
}

bool CoreApp::init()
{
	loadParam();
	m_dataController = new DataProcessor();
	m_dataController->initModels();
	m_dataController->loadData();
	m_mainWindow = new WindowManager();
	m_mainWindow->setWindowTitle("Test app");
	m_mainWindow->show();
	return true;
}

void CoreApp::loadParam()
{
	QSettings Settings("param.ini", QSettings::IniFormat);
	Settings.beginGroup("FilesPath");
	m_deviceFilePath = Settings.value("deviceFile").toString();
	m_DDSFilePath = Settings.value("DDSFile").toString();
	m_docFilePath = Settings.value("docsFile").toString();
	m_stageFilePath = Settings.value("stageFile").toString();
	Settings.endGroup();
	Settings.beginGroup("FilterParam");
	m_manualFltr = Settings.value("manualFilter").toString();
	m_firmwareFltr = Settings.value("FirmWareFilter").toString();
	Settings.endGroup();
#ifdef _MSC_VER
	m_deviceFilePath = m_deviceFilePath.replace('\\', '/');
	m_DDSFilePath = m_DDSFilePath.replace('\\', '/');
	m_docFilePath = m_docFilePath.replace('\\', '/');
	m_stageFilePath = m_stageFilePath.replace('\\', '/');
#endif
}

void CoreApp::saveParam()
{
	QSettings Settings("param.ini", QSettings::IniFormat);
	Settings.beginGroup("FilesPath");
	Settings.setValue("deviceFile",m_deviceFilePath);
	Settings.setValue("DDSFile",m_DDSFilePath);
	Settings.setValue("docsFile",m_docFilePath);
	Settings.setValue("stageFile",m_stageFilePath);
	Settings.endGroup();
	Settings.beginGroup("FilterParam");
	Settings.setValue("manualFilter",m_manualFltr);
	Settings.setValue("FirmWareFilter", m_firmwareFltr);
	Settings.endGroup();
}

void CoreApp::writeParam(QWidget* w)
{
	if (w)
	{
		QSettings Settings("param.ini", QSettings::IniFormat);
		Settings.beginGroup(w->objectName());
		Settings.setValue("pos", w->pos());
		Settings.setValue("size", w->size());
		Settings.setValue("maximized", w->isMaximized());
		Settings.endGroup();
	}
}

void CoreApp::readParam(QWidget* w)
{
	if (w)
	{
		QSettings Settings("param.ini", QSettings::IniFormat);
		Settings.beginGroup(w->objectName());
		w->move(Settings.value("pos").toPoint());
		if (!Settings.value("maximized").toBool())
			w->resize(Settings.value("size").toSize());
		else
			w->setWindowState(Qt::WindowMaximized);
	}
}

