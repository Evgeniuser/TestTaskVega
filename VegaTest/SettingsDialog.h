#pragma once
#include <qdialog.h>
#include <QGroupBox>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QDialogButtonBox>

class SettingsDialog :
    public QDialog
{
public:

	SettingsDialog(QWidget* parent = nullptr);
private:
	void updateData() const;
	void saveData();
	QGroupBox* m_filePathBox;
	QGroupBox* m_fltrParamBox;
	QLineEdit* m_deviceFilePath;
	QLineEdit* m_stageFilePath;
	QLineEdit* m_docsFilePath;
	QLineEdit* m_DDSFilePath;
	QLineEdit* m_manualFltrParam;
	QLineEdit* m_firmwareFltrParam;
	QDialogButtonBox* m_buttonBox;
};

