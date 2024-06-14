#include "PasswordChangerDialog.hpp"

#include <qcheckbox.h>
#include <qobject.h>
#include <qtoolbutton.h>

#include "RandomizedPasswordDialog.hpp"

PasswordChangerDialog::PasswordChangerDialog(QWidget *parent) : QDialog(parent),
                                                                m_ui(new Ui::PasswordChangerDialog) {
    m_ui->setupUi(this);
    connect(this->m_ui->showPasswordCB, &QCheckBox::stateChanged, this, &PasswordChangerDialog::sl_showPasswordCheckStateChanged);
    connect(this->m_ui->showNewPasswordCB, &QCheckBox::stateChanged, this, &PasswordChangerDialog::sl_showPasswordCheckStateChanged);
    connect(this->m_ui->generatePasswordTB, &QToolButton::clicked, this, &PasswordChangerDialog::sl_generatePasswordTBClicked);
}

PasswordChangerDialog::~PasswordChangerDialog() {
    delete m_ui;
}

void PasswordChangerDialog::sl_showPasswordCheckStateChanged(int state) {
    // get sender
    auto *sender = qobject_cast<QCheckBox *>(QObject::sender());
    if (sender == this->m_ui->showNewPasswordCB) {
        if (state == Qt::Checked) {
            this->m_ui->newPasswordLE1->setEchoMode(QLineEdit::Normal);
            this->m_ui->newPasswordLE2->setEchoMode(QLineEdit::Normal);
        } else {
            this->m_ui->newPasswordLE1->setEchoMode(QLineEdit::Password);
            this->m_ui->newPasswordLE2->setEchoMode(QLineEdit::Password);
        }
    } else if (sender == this->m_ui->showPasswordCB) {
        if (state == Qt::Checked) {
            this->m_ui->currentPasswordLE->setEchoMode(QLineEdit::Normal);
        } else {
            this->m_ui->currentPasswordLE->setEchoMode(QLineEdit::Password);
        }
    }
}

void PasswordChangerDialog::sl_generatePasswordTBClicked(bool checked) {
    RandomizedPasswordDialog dialog;
    dialog.exec();
    auto createdPassword = dialog.getGeneratedPassword();
    if (!createdPassword.isEmpty() && !createdPassword.isNull()) {
        this->m_ui->newPasswordLE1->setText(createdPassword);
        this->m_ui->newPasswordLE2->setText(createdPassword);
        // todo: copy to clipboard
    }
}