#include "RandomizedPasswordDialog.hpp"

#include "../design/ui_RandomizedPasswordDialog.h"
#include "RandomizedPassword.hpp"

RandomizedPasswordDialog::RandomizedPasswordDialog(QWidget *parent) : QDialog(parent),
                                                                      m_ui(new Ui::RandomizedPasswordDialog) {
    m_ui->setupUi(this);
    this->initConnections();
    this->m_ui->passwordLengthIndicator->setText(QString::number(this->m_ui->passwordLengthSlider->value()));
}

RandomizedPasswordDialog::~RandomizedPasswordDialog() {
    delete m_ui;
}

void RandomizedPasswordDialog::initConnections() {
    connect(this->m_ui->checkLowerCase, &QCheckBox::toggled, this, &RandomizedPasswordDialog::sl_checkBoxToggled);
    connect(this->m_ui->checkUpperCase, &QCheckBox::toggled, this, &RandomizedPasswordDialog::sl_checkBoxToggled);
    connect(this->m_ui->checkDigits, &QCheckBox::toggled, this, &RandomizedPasswordDialog::sl_checkBoxToggled);
    connect(this->m_ui->checkDigits, &QCheckBox::toggled, this, &RandomizedPasswordDialog::sl_checkBoxToggled);

    connect(this->m_ui->generateButton, &QPushButton::clicked, this, &RandomizedPasswordDialog::sl_generateClicked);
    connect(this->m_ui->copyTB, &QPushButton::clicked, this, &RandomizedPasswordDialog::sl_copyClicked);
    connect(this->m_ui->showPasswordCheck, &QCheckBox::stateChanged, this, &RandomizedPasswordDialog::sl_showPassword);
    connect(this->m_ui->passwordLengthSlider, &QSlider::valueChanged, this, &RandomizedPasswordDialog::sl_valueChanged);
}

void RandomizedPasswordDialog::sl_generateClicked(bool clicked) {
    int lengthOfPassword = this->m_ui->passwordLengthSlider->value();
    int checkedCount = 0;
    foreach (QObject *child, this->m_ui->groupBox->findChildren<QCheckBox *>()) {
        auto *checkBox = qobject_cast<QCheckBox *>(child);
        if (checkBox && checkBox->isChecked()) {
            checkedCount++;
        }
    }

    if (checkedCount == 0) {
        QMessageBox::warning(this, tr("Error"), tr("You have to select at least 1 character set"));
        return;
    }

    bool lowercase = this->m_ui->checkLowerCase->isChecked();
    bool uppercase = this->m_ui->checkUpperCase->isChecked();
    bool digits = this->m_ui->checkDigits->isChecked();
    bool special = this->m_ui->checkSpecial->isChecked();

    auto set = static_cast<RandomizedPassword::CharacterSet>(0);
    if (lowercase) set = static_cast<RandomizedPassword::CharacterSet>(set | RandomizedPassword::LOWERCASE);
    if (uppercase) set = static_cast<RandomizedPassword::CharacterSet>(set | RandomizedPassword::UPPERCASE);
    if (digits) set = static_cast<RandomizedPassword::CharacterSet>(set | RandomizedPassword::DIGITS);
    if (special) set = static_cast<RandomizedPassword::CharacterSet>(set | RandomizedPassword::SPECIAL);

    RandomizedPassword random(set, lengthOfPassword, this);
    auto password = random.getRandomizedPassword();
    if (password.length() <= 0) {
        QMessageBox::warning(this, tr("Error"), tr("Random password cannot be created"));
    }
    this->m_ui->passwordLE->setText(password);
    this->m_generatedPassword = password;
}

void RandomizedPasswordDialog::sl_checkBoxToggled(bool toggle) {
    auto *senderCheckBox = qobject_cast<QCheckBox *>(sender());
    if (senderCheckBox) {
        // Count checked checkboxes
        int checkedCount = 0;
        foreach (QObject *child, this->m_ui->groupBox->findChildren<QCheckBox *>()) {
            auto *checkBox = qobject_cast<QCheckBox *>(child);
            if (checkBox && checkBox->isChecked()) {
                checkedCount++;
            }
        }

        // If no checkbox is checked, recheck the sender checkbox
        if (checkedCount == 0) {
            QMessageBox::warning(this, tr("Error"), tr("There must be at least 1 state."));

            senderCheckBox->setChecked(true);
        }
    }
}

void RandomizedPasswordDialog::sl_showPassword(int state) {
    if (state == Qt::Checked) {
        this->m_ui->passwordLE->setEchoMode(QLineEdit::Normal);
    } else {
        this->m_ui->passwordLE->setEchoMode(QLineEdit::Password);
    }
}

void RandomizedPasswordDialog::sl_copyClicked(bool checked) {
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(this->m_ui->passwordLE->text());
}

void RandomizedPasswordDialog::sl_valueChanged(int value) {
    this->m_ui->passwordLengthIndicator->setText(QString::number(value));
}
