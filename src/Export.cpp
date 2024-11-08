#include "Export.hpp"

#include "DataDirs.hpp"
#include "ExportDialog.hpp"
#include "singleton.hpp"

Export::Export(QObject *base) : QObject(base) {
    QStringList paths = Singleton<DataDirs>::Instance().GetDataDirPaths();
    paths << QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    // get every *.enc files from paths
    QStringList encFiles;
    for (const auto &path : paths) {
        QDir dir(path);
        if (!dir.exists()) {
            Logger::log_static(LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__, QObject::tr("Data directory not exists: %1. Trying to create.").arg(path).toStdString());
            if (!dir.mkpath(path))
                Logger::log_static(LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__, QObject::tr("Data directory cannot be created: %1.").arg(path).toStdString());
        }
        auto encFilesInDir = dir.entryList(QStringList() << "*.enc", QDir::Files);
        if (encFilesInDir.isEmpty())
            Logger::log_static(LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__, QObject::tr("There is no encrypted files in: %1. Skipping").arg(path).toStdString());
        else
            for (const auto &fileName : encFilesInDir) encFiles << dir.filePath(fileName);
    }

    if (encFiles.isEmpty()) {
        QString text = QObject::tr("There are no encrypted files on or not exists");
        Logger::log_static(LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__, text.toStdString());
        QMessageBox::question(nullptr, QObject::tr("Export Error"), text);
        return;
    }

    // get export directory
    auto &dialog = Singleton<ExportDialog>::Instance(encFiles);
    if (dialog.exec() == QDialog::Accepted) {
        QStringList files = dialog.GetSelectedFiles();
        QString path = dialog.GetSelectedDirectory();

        for (const QString &file : files) {
            QFileInfo info(file);
            QString sourcePath = file;
            QString destinationPath = path + QDir::separator() + info.fileName();

            // Check if source file exists
            if (!QFile::exists(sourcePath)) {
                Logger::log_static(LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__, QObject::tr("Source file does not exist: %1").arg(sourcePath).toStdString());
                QMessageBox::warning(nullptr, tr("Copy Error"), tr("Source file does not exist: %1").arg(sourcePath));
                continue;
            }

            // Check if destination file already exists
            if (QFile::exists(destinationPath)) {
                Logger::log_static(LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__, QObject::tr("Destination file already exists: %1").arg(destinationPath).toStdString());
                QMessageBox::warning(nullptr, tr("Copy Error"), tr("Destination file already exists: %1").arg(destinationPath));
                continue;
            }

            // Attempt to copy file
            if (QFile::copy(sourcePath, destinationPath)) {
                Logger::log_static(LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__, QObject::tr("Copied '%1' to '%2'").arg(sourcePath, destinationPath).toStdString());
            } else {
                Logger::log_static(LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__, QObject::tr("Failed to copy file '%1' to '%2'").arg(sourcePath, destinationPath).toStdString());
                QMessageBox::warning(nullptr, tr("Copy Error"), tr("Failed to copy file '%1' to '%2'").arg(sourcePath, destinationPath));
            }
        }
    }
}