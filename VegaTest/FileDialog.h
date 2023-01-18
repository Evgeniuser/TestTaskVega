#pragma once

#include <QPushButton>
#include <QWidget>
#include <QDialogButtonBox>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>

class FileDialog : public QDialog
{
    Q_OBJECT

public:
    FileDialog(int flType, QString dlgName, QString devName, QString stageName, QWidget* parent = nullptr);
    FileDialog(int flType, QString dlgName, QString devName, QString stageName, QString fileName, QString filePath, QWidget* parent = nullptr);
    QVariantList getData() const;
private:
    void initUi(QWidget* parents);

    QLineEdit* m_deviceName;
    QLineEdit* m_stageName;
    QLineEdit* m_filePath;
    QLineEdit* m_fileName;
    QPushButton* m_selectFile;
    QPushButton* m_Ok;
    QPushButton* m_cancel;
    QDialogButtonBox* m_buttonBox;

    int m_flType = 0;
};