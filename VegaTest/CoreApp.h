#pragma once

#include <QApplication>
#include <QObject>


#include "WindowManager.h"
#include "DataProcessor.h"

class CoreApp final : public QApplication
{
	Q_OBJECT

public:
	CoreApp(int& argc, char** argv);
	static CoreApp* app() { return m_app; }
	static void writeParam(QWidget* w);
	static void readParam(QWidget* w);

	DataProcessor* data() const { return m_dataController; }
	bool init();

	const QString& deviceFilePath() const { return m_deviceFilePath; }
	const QString& stageFilePath() const { return m_stageFilePath; }
	const QString& docFilePath() const { return m_docFilePath; }
	const QString& DDSFilePath() const { return m_DDSFilePath; }
	const QString& manualFltr() const { return m_manualFltr; }
	const QString& firmwareFltr() const { return m_firmwareFltr; }
	void setDeviceFilePath(const QString& deviceFilePath) { m_deviceFilePath = deviceFilePath; }
	void setStageFilePath(const QString& setStageFilePath) { m_stageFilePath = setStageFilePath; }
	void setDocFilePath(const QString& docFilePath) { m_docFilePath = docFilePath; }
	void setDDSFilePath(const QString& DDSFilePath) { m_DDSFilePath = DDSFilePath; }
	void setManualFltr(const QString& manualFltr) { m_manualFltr = manualFltr; }
	void setFirmwareFltr(const QString& firmwareFltr) { m_firmwareFltr = firmwareFltr; }

	~CoreApp() override;
	CoreApp(const CoreApp& other) = delete;
	CoreApp(CoreApp&& other) = delete;
	CoreApp& operator=(const CoreApp& other) = delete;
	CoreApp& operator=(CoreApp&& other) = delete;

private:

	void loadParam();
	void saveParam();
	WindowManager* m_mainWindow{};
	DataProcessor* m_dataController{};

	QString m_deviceFilePath;
	QString m_stageFilePath;
	QString m_docFilePath;
	QString m_DDSFilePath;
	QString m_manualFltr;
	QString m_firmwareFltr;
	static CoreApp* m_app;
};
