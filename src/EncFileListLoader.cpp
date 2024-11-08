#include "EncFileListLoader.hpp"

#include <QSet>
#include <QStandardItemModel>

#include "DataDirs.hpp"
#include "EncFileListLoaderException.hpp"
#include "singleton.hpp"

EncFileListLoader::EncFileListLoader(QComboBox* comboBox) : m_comboBox(comboBox) {
    comboBox->clear();
    this->LoadEncFiles();
}

void EncFileListLoader::LoadEncFiles() {
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

    auto& dataDirs = Singleton<DataDirs>::Instance();
    for (const auto& dataDir : dataDirs.GetDataDirs()) {
        QDir dir(dataDir.GetPath());
        encFiles.append(dir.entryInfoList(filters, QDir::Files));
    }

    // add file names to combobox
    QSet<QString> uniqueFilePaths;
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(m_comboBox->model());

    for (std::size_t i = 0; i < encFiles.count(); i++) {
        QString fileName = encFiles.at(i).fileName().mid(0, encFiles.at(i).fileName().length() - 4);
        QString absoluteFilePath = encFiles.at(i).absoluteFilePath();

        // name in box
        m_comboBox->addItem(fileName);

        // filter repeating absolutefilepaths
        if (!uniqueFilePaths.contains(absoluteFilePath)) {
            model->item(i)->setToolTip(absoluteFilePath);
            uniqueFilePaths.insert(absoluteFilePath);
        }
    }
}