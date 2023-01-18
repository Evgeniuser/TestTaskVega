#include "SettingsDialog.h"

#include <QFormLayout>

#include "CoreApp.h"

SettingsDialog::SettingsDialog(QWidget* parent) : QDialog(parent)
{
	setModal(true);
	setWindowFlag(Qt::WindowCloseButtonHint, false);
	setWindowFlag(Qt::WindowContextHelpButtonHint, false);
	m_filePathBox = new QGroupBox(QString::fromUtf8("Пути к файлам"), this);
	m_deviceFilePath = new QLineEdit(m_filePathBox);
	m_stageFilePath = new QLineEdit(m_filePathBox);
	m_docsFilePath = new QLineEdit(m_filePathBox);
	m_DDSFilePath = new QLineEdit(m_filePathBox);
	auto fileLayout = new QFormLayout();
	fileLayout->addRow(QString::fromUtf8("Файл описания устройств"), m_deviceFilePath);
	fileLayout->addRow(QString::fromUtf8("Файл описания операций"), m_stageFilePath);
	fileLayout->addRow(QString::fromUtf8("Файл описания файлов"), m_docsFilePath);
	fileLayout->addRow(QString::fromUtf8("Файл описания связей"), m_DDSFilePath);
	m_filePathBox->setLayout(fileLayout);
	m_fltrParamBox = new QGroupBox(QString::fromUtf8("Параметры фильтрации"), this);
	m_manualFltrParam = new QLineEdit(m_fltrParamBox);
	m_firmwareFltrParam = new QLineEdit(m_fltrParamBox);
	auto fltrLayout = new QVBoxLayout();
	fltrLayout->addWidget(new QLabel(QString::fromUtf8("Фильтры для файлов инструкций")));
	fltrLayout->addWidget(m_manualFltrParam);
	fltrLayout->addWidget(new QLabel(QString::fromUtf8("Фильтры для файлов прошивок")));
	fltrLayout->addWidget(m_firmwareFltrParam);
	m_fltrParamBox->setLayout(fltrLayout);
	m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

	auto mainLayout = new QVBoxLayout();
	mainLayout->addWidget(m_filePathBox);
	mainLayout->addWidget(m_fltrParamBox);
	mainLayout->addWidget(m_buttonBox);
	mainLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
	setLayout(mainLayout);

	connect(m_buttonBox, &QDialogButtonBox::accepted, this, [this]() {saveData(); QDialog::accept(); });
	connect(m_buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
	updateData();
}

void SettingsDialog::updateData() const
{
	m_deviceFilePath->setText(CoreApp::app()->deviceFilePath());
	m_stageFilePath->setText(CoreApp::app()->stageFilePath());
	m_docsFilePath->setText(CoreApp::app()->docFilePath());
	m_DDSFilePath->setText(CoreApp::app()->DDSFilePath());
	m_firmwareFltrParam->setText(CoreApp::app()->firmwareFltr());
	m_manualFltrParam->setText(CoreApp::app()->manualFltr());	
}

void SettingsDialog::saveData()
{
	CoreApp::app()->setDeviceFilePath(m_deviceFilePath->text());
	CoreApp::app()->setDocFilePath(m_docsFilePath->text());
	CoreApp::app()->setStageFilePath(m_stageFilePath->text());
	CoreApp::app()->setDDSFilePath(m_DDSFilePath->text());
	CoreApp::app()->setManualFltr(m_manualFltrParam->text());
	CoreApp::app()->setFirmwareFltr(m_firmwareFltrParam->text());
}
