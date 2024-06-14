#include "CreateDialog.hpp"

#include <qcheckbox.h>
#include <qcombobox.h>
#include <qdialog.h>
#include <qmessagebox.h>
#include <qnamespace.h>
#include <qtoolbutton.h>

#include "../design/ui_CreateDialog.h"
#include "CreateEncryptedFile.hpp"
#include "CreateEncryptedFileException.hpp"
#include "EncFileListLoader.hpp"
#include "RandomizedPasswordDialog.hpp"

CreateDialog::CreateDialog(QWidget *parent) : QDialog(parent),
                                              m_ui(new Ui::CreateDialog) {
    m_ui->setupUi(this);
    EncFileListLoader loader(this->m_ui->comboBox);

    connect(this, &QDialog::accepted, this, &CreateDialog::sl_accepted);
    connect(this, &QDialog::rejected, this, &CreateDialog::sl_rejected);
    connect(this->m_ui->showPasswordCheck, &QCheckBox::stateChanged, this, &CreateDialog::sl_checkBoxChanged);
    connect(this->m_ui->generateTB, &QToolButton::clicked, this, &CreateDialog::sl_generateClicked);
}

CreateDialog::~CreateDialog() {
    delete m_ui;
}

void CreateDialog::sl_accepted() {
    // check enteredName in qcombobox or empty
    QString enteredName = this->m_ui->fileNameLE->text();

    // Check if the entered name exists in the combo box
    int index = this->m_ui->comboBox->findText(enteredName, Qt::MatchExactly);

    if (enteredName.isEmpty() || enteredName.isNull() || index >= 0) {
        QMessageBox::warning(this, "Error", "File name is not valid for encryption. Please select not exists and valid file name.");
        return;
    }

    // check password is exists
    QString password = this->m_ui->passwordLE->text();
    if (password.isEmpty() || !password.isValidUtf16()) {
        QMessageBox::warning(this, "Error", "Password is not valid for encryption. Please select valid password.");
        return;
    }

    // Remove the file extension if it exists
    QFileInfo fileInfo(enteredName);
    QString fileName = fileInfo.baseName();  // Get the file name without extension

    try {
        CreateEncryptedFile(fileName, password);
    } catch (const CreateEncryptedFileException &e) {
        QMessageBox::critical(this, "Exception Occured", e.message());
        return;
    }

    this->m_isCreated = true;

    qDebug() << "Accepted";
}

void CreateDialog::sl_rejected() {
    qDebug() << "Rejected";
}

void CreateDialog::sl_checkBoxChanged(int state) {
    if (state == Qt::Checked) {
        this->m_ui->passwordLE->setEchoMode(QLineEdit::Normal);
    } else {
        this->m_ui->passwordLE->setEchoMode(QLineEdit::Password);
    }
}

void CreateDialog::sl_generateClicked(bool checked) {
    RandomizedPasswordDialog dialog;
    dialog.exec();
    auto createdPassword = dialog.getGeneratedPassword();
    if (!createdPassword.isEmpty() && !createdPassword.isNull()) {
        this->m_ui->passwordLE->setText(createdPassword);
        // todo: copy to clipboard
    }
}