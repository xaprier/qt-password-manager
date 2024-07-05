#include "EncFileListLoader.hpp"

#include "EncFileListLoaderException.hpp"

EncFileListLoader::EncFileListLoader(QComboBox* comboBox) : comboBox(comboBox) {
    comboBox->clear();
    this->loadEncFiles();
}

void EncFileListLoader::loadEncFiles() {
    // get default qsettings directory for getting files
    QString settingsPath = QSettings("xaprier", "Password Manager").fileName();
    QFileInfo settingsFileInfo(settingsPath);
    QDir settingsDir = settingsFileInfo.dir();

    // create path if not exists
    QDir dir(settingsFileInfo.absolutePath());
    if (!dir.exists()) {
        if (!dir.mkpath(settingsFileInfo.absolutePath())) {
            throw EncFileListLoaderException(QObject::tr("Failed to create directory: %1").arg(settingsFileInfo.absolutePath()));
        }
    }

    // get files with .enc extension
    QStringList filters;
    filters << "*.enc";
    QFileInfoList encFiles = settingsDir.entryInfoList(filters, QDir::Files);

    // add file names to combobox
    for (const QFileInfo& fileInfo : encFiles) {
        comboBox->addItem(fileInfo.fileName().mid(0, fileInfo.fileName().length() - 4));
    }
}