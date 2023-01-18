#pragma once

#include <QMainWindow>
#include <QListWidget>
#include <QTabWidget>
#include <QComboBox>
#include <QLayout>
#include <QPushButton>
#include <QMenuBar>
#include <QStatusBar>

#include "CentralWindow.h"

class WindowManager  : public QMainWindow
{
	Q_OBJECT

public:
	WindowManager(QWidget *parent = nullptr);
	~WindowManager();

private:
	void CreateMenu();

	CentralWindow* m_centralWindow;
	QMenuBar* m_menuBar;
	QStatusBar* m_statusBar{};
};
