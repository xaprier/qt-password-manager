#include "LoginDialog.hpp"

#include <qdialog.h>
#include <qdialogbuttonbox.h>
#include <qmessagebox.h>
#include <qtoolbutton.h>

#include "../design/ui_LoginDialog.h"
#include "Auth.hpp"
#include "CreateDialog.hpp"
#include "EncFileListLoader.hpp"

LoginDialog::LoginDialog(QWidget* parent) : QDialog(parent),
                                            m_ui(new Ui::LoginDialog) {
    m_ui->setupUi(this);
    EncFileListLoader loader(this->m_ui->encryptedFiles);

    if (this->m_ui->encryptedFiles->count() <= 0) {
        auto msgBox = QMessageBox(QMessageBox::Icon::Warning, "No encrypted database found", "There is no encrypted databases. Do you want to create one", QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No);
        if (msgBox.exec() == QMessageBox::StandardButton::Yes) {
            CreateDialog d;
            while (!d.isCreated()) {
                if (d.exec() == QDialog::Rejected) break;
            }

            if (d.isCreated()) {  // if there is a created one, update combobox again
                EncFileListLoader loader(this->m_ui->encryptedFiles);
            }
        }
    }
    connect(this, &QDialog::accepted, this, &LoginDialog::sl_accepted);
    connect(this, &QDialog::rejected, this, &LoginDialog::sl_rejected);
    connect(this->m_ui->newButton, &QToolButton::clicked, this, &LoginDialog::sl_newClicked);
    connect(this->m_ui->showPasswordCheck, &QCheckBox::stateChanged, this, &LoginDialog::sl_checkBoxChanged);
}

LoginDialog::~LoginDialog() {
    delete m_ui;
}

void LoginDialog::sl_accepted() {
    // check the count of combobox
    auto combobox = this->m_ui->encryptedFiles;

    if (combobox->currentIndex() == -1) {
        QMessageBox::warning(this, "Error", "No encrypted file selected. Please select an encrypted file.");
        return;
    }

    // check the password is empty
    auto passwordLine = this->m_ui->passwordLine;
    QString password = passwordLine->text();
    if (password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Password cannot be empty. Please enter a password.");
        return;
    }

    QString selectedFile = combobox->currentText();
    QString settingsPath = QSettings("xaprier", "Password Manager").fileName();
    QFileInfo settingsFileInfo(settingsPath);
    QString fullFilePath = settingsFileInfo.absolutePath() + "/" + selectedFile + ".enc";
    if (verifyPassword(fullFilePath, password)) {
        this->m_masterPassword = password;
        this->m_filePath = fullFilePath;
        this->setLogged(true);
        QMessageBox::information(this, "Success", "Login successful for file: " + selectedFile);
    } else {
        QMessageBox::warning(this, "Error", "Invalid password. Please try again.");
    }
}

void LoginDialog::sl_rejected() {
    QApplication::quit();
}

bool LoginDialog::verifyPassword(const QString& filePath, const QString& password) {
    qDebug() << "path : " << filePath;
    Auth authorizer(filePath, password);
    return authorizer.isAuthorized();
}

void LoginDialog::sl_newClicked(bool checked) {
    CreateDialog d;
    while (!d.isCreated()) {
        if (d.exec() == QDialog::Rejected) break;
    }

    if (d.isCreated()) {  // if there is a created one, update combobox again
        EncFileListLoader loader(this->m_ui->encryptedFiles);
    }
}

void LoginDialog::sl_checkBoxChanged(int state) {
    if (state == Qt::Checked) {
        this->m_ui->passwordLine->setEchoMode(QLineEdit::Normal);
    } else {
        this->m_ui->passwordLine->setEchoMode(QLineEdit::Password);
    }
}