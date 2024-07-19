#include "NameChangerDialog.hpp"

NameChangerDialog::NameChangerDialog(QWidget *parent) : QDialog(parent),
                                                        m_ui(new Ui::NameChangerDialog) {
    m_ui->setupUi(this);
    connect(this->m_ui->showPasswordCB, &QCheckBox::stateChanged, this, &NameChangerDialog::sl_showPasswordCheckStateChanged);
}

NameChangerDialog::~NameChangerDialog() {
    delete m_ui;
}

void NameChangerDialog::sl_showPasswordCheckStateChanged(int state) {
    if (state == Qt::Checked) {
        this->m_ui->currentPasswordLE->setEchoMode(QLineEdit::Normal);
    } else {
        this->m_ui->currentPasswordLE->setEchoMode(QLineEdit::Password);
    }
}