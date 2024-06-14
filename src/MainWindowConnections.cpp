#include "MainWindowConnections.hpp"

#include <qjsonobject.h>
#include <qmessagebox.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qtoolbutton.h>

#include "RandomizedPasswordDialog.hpp"

void MainWindowConnections::sl_generateTBClicked(bool checked) {
    RandomizedPasswordDialog dialog;
    dialog.exec();
    auto createdPassword = dialog.getGeneratedPassword();
    if (!createdPassword.isEmpty() && !createdPassword.isNull()) {
        this->m_ui->passwordLE->setText(createdPassword);
    }
}

void MainWindowConnections::sl_showPasswordCBStateChanged(int state) {
    if (state == Qt::Checked) {
        this->m_ui->passwordLE->setEchoMode(QLineEdit::Normal);
    } else {
        this->m_ui->passwordLE->setEchoMode(QLineEdit::Password);
    }
}

void MainWindowConnections::sl_createPBClicked(bool checked) {
    const QString name = this->m_ui->nameLE->text();
    const QString password = this->m_ui->passwordLE->text();
    const QString platformName = this->m_ui->platformCombo->currentText();

    // make sure everything is filled
    bool isNameEmpty = name.isEmpty();
    bool isPasswordEmpty = password.isEmpty();
    bool isPlatformNotSelected = this->m_ui->platformCombo->currentIndex() == -1;

    if (isNameEmpty || isPasswordEmpty || isPlatformNotSelected) {
        QMessageBox::warning(this->m_base, "Error", "Please fill all fields");
        return;
    }

    // check there is created one with same name and same platform
    auto array = this->m_base->m_jsonHandler->platforms();
    bool samePlatform = false;
    bool sameName = false;
    for (const auto &item : array) {
        if (item.isObject()) {
            auto object = item.toObject();
            if (object["name"].toString() == name) sameName = true;
            auto platform = Platform::fromJson(object);
            if (platform->name() == platformName) {
                samePlatform = true;
            }
        }
    }

    if (samePlatform && sameName) {
        QMessageBox::warning(this->m_base, "Error", "There is another one with same name and same platform.\nPlease edit it or create with using another inputs.");
        return;
    }

    QJsonObject object;
    object["name"] = name;
    object["platform"] = platformName;
    object["password"] = password;

    array.append(object);  // add to qjsonarray

    qDebug() << "Array: " << array;

    // update the array
    this->m_base->m_jsonHandler->setPlatforms(array);

    // load platforms again
    this->m_base->loadPlatforms();

    // remove selection
    this->m_ui->platformsLW->clearSelection();
}

void MainWindowConnections::sl_deletePBClicked(bool checked) {
    bool isPlatformNotSelected = this->m_ui->platformsLW->selectedItems().isEmpty();
    if (isPlatformNotSelected) {
        QMessageBox::warning(this->m_base, "Error", "There is no selected platform to delete.");
        return;
    }

    // get index of platform
    int index = this->m_ui->platformsLW->currentRow();

    // remove index from jsonarray
    auto array = this->m_base->m_jsonHandler->platforms();
    if (array.size() < index || index < 0) {
        QMessageBox::warning(this->m_base, "Error", "Index error. There is no platform with that index.");
        return;
    }

    QMessageBox msg(QMessageBox::Icon::Warning, "Confirm", "Are you sure to delete?", QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No);
    if (msg.exec() == QMessageBox::StandardButton::No) return;

    array.removeAt(index);

    // update the array
    this->m_base->m_jsonHandler->setPlatforms(array);

    // load platforms again
    this->m_base->loadPlatforms();

    // remove selection
    this->m_ui->platformsLW->clearSelection();
}

void MainWindowConnections::sl_itemClickedLW(QListWidgetItem *item) {
    // get index from item
    QListWidget *listWidget = item->listWidget();
    int index = listWidget->row(item);

    // clear fields
    this->m_ui->nameLE->clear();
    this->m_ui->passwordLE->clear();
    this->m_ui->platformCombo->setCurrentIndex(-1);
    this->m_ui->showPasswordCB->setCheckState(Qt::Unchecked);

    // get item information
    auto array = this->m_base->m_jsonHandler->platforms();
    if (array.size() < index || index < 0) {
        QMessageBox::warning(this->m_base, "Error", "Index error. There is no platform with that index.");
        return;
    }

    auto object = array.at(index);
    QString name = object["name"].toString();
    QString platformName = object["platform"].toString();
    QString password = object["password"].toString();

    // fill item information
    this->m_ui->nameLE->setText(name);
    this->m_ui->passwordLE->setText(password);
    int firstIndex = this->m_ui->platformCombo->findText(platformName, Qt::MatchFixedString);
    this->m_ui->platformCombo->setCurrentIndex(firstIndex);
}

void MainWindowConnections::sl_updatePBClicked(bool checked) {
    const QString name = this->m_ui->nameLE->text();
    const QString password = this->m_ui->passwordLE->text();
    const QString platformName = this->m_ui->platformCombo->currentText();

    // make sure everything is filled
    bool isNameEmpty = name.isEmpty();
    bool isPasswordEmpty = password.isEmpty();
    bool isPlatformNotSelected = this->m_ui->platformCombo->currentIndex() == -1;

    if (isNameEmpty || isPasswordEmpty || isPlatformNotSelected) {
        QMessageBox::warning(this->m_base, "Error", "Please fill all fields");
        return;
    }

    int index = this->m_ui->platformsLW->currentRow();
    auto array = this->m_base->m_jsonHandler->platforms();
    if (array.size() < index || index < 0) {
        QMessageBox::warning(this->m_base, "Error", "Index error. There is no platform with that index.");
        return;
    }

    // check there is created one with same name and same platform
    bool samePlatform = false;
    bool sameName = false;
    for (const auto &item : array) {
        if (item == array.at(index)) continue;
        if (item.isObject()) {
            auto object = item.toObject();
            if (object["name"].toString() == name) sameName = true;
            auto platform = Platform::fromJson(object);
            if (platform->name() == platformName) {
                samePlatform = true;
            }
        }
    }

    if (samePlatform && sameName) {
        QMessageBox::warning(this->m_base, "Error", "There is another one with same name and same platform.\nPlease edit it or create with using another inputs.");
        return;
    }

    QMessageBox msg(QMessageBox::Icon::Warning, "Confirm", "Are you sure to update?", QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No);
    if (msg.exec() == QMessageBox::StandardButton::No) return;

    QJsonObject object = array.at(index).toObject();
    object["name"] = name;
    object["platform"] = platformName;
    object["password"] = password;

    array[index] = object;

    qDebug() << "Array: " << array;

    // update the array
    this->m_base->m_jsonHandler->setPlatforms(array);

    // load platforms again
    this->m_base->loadPlatforms();

    // remove selection
    this->m_ui->platformsLW->clearSelection();
}