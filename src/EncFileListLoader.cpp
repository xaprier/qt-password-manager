#include "EncFileListLoader.hpp"

#include "EncFileListLoaderException.hpp"

EncFileListLoader::EncFileListLoader(QComboBox* comboBox) : comboBox(comboBox) {
    comboBox->clear();
    this->loadEncFiles();
}

void EncFileListLoader::loadEncFiles() {
    // get appdata path
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    // create path if not exists
    QDir dir(appDataPath);
    if (!dir.exists()) {
        if (!dir.mkpath(appDataPath)) {
            throw EncFileListLoaderException(QObject::tr("Failed to create directory: %1").arg(appDataPath));
        }
    }

    // get files with .enc extension
    QStringList filters;
    filters << "*.enc";
    QFileInfoList encFiles = dir.entryInfoList(filters, QDir::Files);

    // add file names to combobox
    for (const QFileInfo& fileInfo : encFiles) {
        comboBox->addItem(fileInfo.fileName().mid(0, fileInfo.fileName().length() - 4));
    }
}