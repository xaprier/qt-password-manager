#include "LoginDialog.hpp"

#include "../design/ui_LoginDialog.h"
#include "Auth.hpp"
#include "CreateDialog.hpp"
#include "DataDirHandlerDialog.hpp"
#include "EncFileListLoader.hpp"
#include "Export.hpp"
#include "Import.hpp"

LoginDialog::LoginDialog(QWidget* parent) : QDialog(parent),
                                            m_ui(new Ui::LoginDialog) {
    m_ui->setupUi(this);
    EncFileListLoader loader(this->m_ui->encryptedFiles);

    if (this->m_ui->encryptedFiles->count() <= 0) {
        auto msgBox = QMessageBox(QMessageBox::Icon::Warning, tr("No encrypted database found"), tr("There is no encrypted databases. Do you want to create one"), QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No);
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
    connect(this->m_ui->importButton, &QToolButton::clicked, this, &LoginDialog::sl_importClicked);
    connect(this->m_ui->exportButton, &QToolButton::clicked, this, &LoginDialog::sl_exportClicked);
    connect(this->m_ui->updateDataDirButton, &QToolButton::clicked, this, &LoginDialog::sl_updateClicked);
}

LoginDialog::~LoginDialog() {
    delete m_ui;
}

void LoginDialog::sl_accepted() {
    // check the count of combobox
    auto combobox = this->m_ui->encryptedFiles;

    if (combobox->currentIndex() == -1) {
        QMessageBox::warning(this, tr("Error"), tr("No encrypted file selected. Please select an encrypted file."));
        return;
    }

    // check the password is empty
    auto passwordLine = this->m_ui->passwordLE;
    QString password = passwordLine->text();
    if (password.isEmpty()) {
        QMessageBox::warning(this, tr("Error"), tr("Password cannot be empty. Please enter a password."));
        return;
    }

    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(combobox->model());
    QString selectedFile = model->item(combobox->currentIndex())->toolTip();
    if (verifyPassword(selectedFile, password)) {
        this->m_masterPassword = password;
        this->m_filePath = selectedFile;
        this->setLogged(true);
    } else {
        QMessageBox::warning(this, tr("Error"), tr("Invalid password. Please try again."));
    }
}

void LoginDialog::sl_rejected() {
    QApplication::quit();
}

bool LoginDialog::verifyPassword(const QString& filePath, const QString& password) {
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
        this->m_ui->passwordLE->setEchoMode(QLineEdit::Normal);
    } else {
        this->m_ui->passwordLE->setEchoMode(QLineEdit::Password);
    }
}

void LoginDialog::sl_importClicked(bool checked) {
    Import import;
    EncFileListLoader loader(this->m_ui->encryptedFiles);  // load encrypted files again
}

void LoginDialog::sl_exportClicked(bool checked) {
    Export exp;
}

void LoginDialog::sl_updateClicked(bool checked) {
    DataDirHandlerDialog dialog;
    dialog.exec();
    EncFileListLoader loader(this->m_ui->encryptedFiles);
}
