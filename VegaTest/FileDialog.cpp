#include "FileDialog.h"
#include <QLayout>
#include <QFileDialog>

FileDialog::FileDialog(QString dlgName, QString devName, QString stageName, QWidget* parent)
	: QDialog(parent)
{
	setWindowTitle(dlgName);
	initUi(this);
	m_deviceName->setText(devName);
	m_stageName->setText(stageName);

	adjustSize();
}

FileDialog::FileDialog(QString dlgName, QString devName, QString stageName, QString fileName, QString filePath,
	QWidget* parent) :QDialog(parent)
{
	setWindowTitle(dlgName);
	initUi(this);
	m_deviceName->setText(devName);
	m_stageName->setText(stageName);
	m_fileName->setText(fileName);
	m_filePath->setText(filePath);
	adjustSize();
}

void FileDialog::initUi(QWidget* parent)
{
	setWindowFlag(Qt::WindowCloseButtonHint, false);
	setWindowFlag(Qt::WindowContextHelpButtonHint, false);
	QLabel* devLable = new QLabel(QString::fromUtf8("Устройства:"), parent);
	devLable->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
	m_deviceName = new QLineEdit(parent);
	m_deviceName->setDisabled(true);
	m_stageName = new QLineEdit(parent);
	m_stageName->setDisabled(true);
	QLabel* fpLable = new QLabel(QString::fromUtf8("Путь к файлу:"), parent);
	fpLable->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
	m_filePath = new QLineEdit(parent);
	QLabel* fnLable = new QLabel(QString::fromUtf8("Имя файла"), parent);
	fnLable->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
	m_fileName = new QLineEdit(parent);
	QLabel* divLine = new QLabel("<hr></hr>", parent);
	divLine->setFont(QFont("arial", 1, 1));
	divLine->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));
	m_selectFile = new QPushButton(QString::fromUtf8("..."), parent);
	m_selectFile->setFixedWidth(25);
	m_selectFile->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
	m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, parent);

	auto nameLayout = new QHBoxLayout();
	nameLayout->addWidget(devLable);
	nameLayout->addWidget(m_deviceName);
	nameLayout->addWidget(new QLabel(QString::fromUtf8("Имя операции:")));
	nameLayout->addWidget(m_stageName);

	auto mainLayout = new QGridLayout();
	mainLayout->addLayout(nameLayout, 0, 0, 1, 3);
	mainLayout->addWidget(divLine, 1, 0, 1, 3);
	mainLayout->addWidget(fpLable, 2, 0);
	mainLayout->addWidget(m_filePath, 2, 1, 1, 1);
	mainLayout->addWidget(m_selectFile, 2, 2, Qt::AlignRight);
	mainLayout->addWidget(fnLable, 3, 0);
	mainLayout->addWidget(m_fileName, 3, 1, 1, 2);
	mainLayout->addWidget(m_buttonBox, 4, 1, 1, 2);
	mainLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 5, 0, 1, 4);
	setLayout(mainLayout);

	connect(m_selectFile, &QPushButton::clicked, this, [this]()
		{
			QString filePath = QFileDialog::getOpenFileName(this, QString::fromUtf8("Выберите файл"));
	m_filePath->setText(filePath);
	QFileInfo fl(filePath);
	m_fileName->setText(fl.baseName());
		});
	auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
		| QDialogButtonBox::Cancel);

	connect(m_buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
	connect(m_buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

QVariantList FileDialog::getData() const
{
	return QVariantList{ m_filePath->text() ,m_fileName->text() };
}
