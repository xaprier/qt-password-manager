#include "PasswordConfirmationDialog.hpp"

PasswordConfirmationDialog::PasswordConfirmationDialog(QWidget *parent) : QDialog(parent),
                                                                          m_ui(new Ui::PasswordConfirmationDialog) {
    m_ui->setupUi(this);
    connect(this->m_ui->showPasswordCB, &QCheckBox::stateChanged, this, &PasswordConfirmationDialog::sl_ShowPasswordStateChanged);
}

PasswordConfirmationDialog::~PasswordConfirmationDialog() {
    delete m_ui;
}

void PasswordConfirmationDialog::sl_ShowPasswordStateChanged(int state) {
    if (state == Qt::Checked) {
        this->m_ui->passwordLE->setEchoMode(QLineEdit::Normal);
    } else {
        this->m_ui->passwordLE->setEchoMode(QLineEdit::Password);
    }
}