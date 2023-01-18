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

	~CoreApp() override;
	CoreApp(const CoreApp& other) = delete;
	CoreApp(CoreApp&& other) = delete;
	CoreApp& operator=(const CoreApp& other) = delete;
	CoreApp& operator=(CoreApp&& other) = delete;
private:

	void loadParam();
	
	WindowManager* m_mainWindow{};
	DataProcessor* m_dataController{};

	QString m_deviceFilePath;
	QString m_stageFilePath;
	QString m_docFilePath;
	QString m_DDSFilePath;

	static CoreApp* m_app;
};
