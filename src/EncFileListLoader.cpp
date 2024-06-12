#include "EncFileListLoader.hpp"

EncFileListLoader::EncFileListLoader(QComboBox* comboBox) : comboBox(comboBox) {
    this->loadEncFiles();
}

void EncFileListLoader::loadEncFiles() {
    // get default qsettings directory for getting files
    QString settingsPath = QSettings().fileName();
    QFileInfo settingsFileInfo(settingsPath);
    QDir settingsDir = settingsFileInfo.dir();

    // get files with .enc extension
    QStringList filters;
    filters << "*.enc";
    QFileInfoList encFiles = settingsDir.entryInfoList(filters, QDir::Files);

    // add file names to combobox
    for (const QFileInfo& fileInfo : encFiles) {
        comboBox->addItem(fileInfo.fileName().mid(0, fileInfo.fileName().length() - 4));
    }
}