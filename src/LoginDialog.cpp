#include "LoginDialog.hpp"

#include <qdialog.h>
#include <qdialogbuttonbox.h>
#include <qmessagebox.h>

#include "../design/ui_LoginDialog.h"
#include "EncFileListLoader.hpp"

LoginDialog::LoginDialog(QWidget* parent) : QDialog(parent),
                                            m_ui(new Ui::LoginDialog) {
    m_ui->setupUi(this);
    EncFileListLoader loader(this->m_ui->encryptedFiles);

    if (this->m_ui->encryptedFiles->count() <= 0) {
        auto msgBox = QMessageBox(QMessageBox::Icon::Warning, "No encrypted database found", "There is no encrypted databases. Do you want to create one", QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No);
        if (msgBox.exec() == QMessageBox::StandardButton::Yes) {
            // TODO add implementation of creating new encrypted database dialog
        }
    }
    connect(this, &QDialog::accepted, this, &LoginDialog::sl_accepted);
    connect(this, &QDialog::rejected, this, &LoginDialog::sl_rejected);
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
    if (verifyPassword(selectedFile, password)) {
        QMessageBox::information(this, "Success", "Login successful. Selected file: " + selectedFile);
        this->setLogged(true);
    } else {
        QMessageBox::warning(this, "Error", "Invalid password. Please try again.");
    }
}

void LoginDialog::sl_rejected() {
    QApplication::quit();
}

bool LoginDialog::verifyPassword(const QString& file, const QString& password) {  // TODO create implementation
    return password == "correctpassword";
}