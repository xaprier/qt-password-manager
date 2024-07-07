#include "Import.hpp"

Import::Import(QObject *base) : QObject(base) {
    QSettings settings("xaprier", "Password Manager", this);
    QFileInfo info(settings.fileName());
    QString fullPath = info.absolutePath();

    ImportDialog dialog;
    if (dialog.exec() == QDialog::Accepted) {
        QStringList files = dialog.getSelectedFiles();
        for (const QString &file : files) {
            QFileInfo info(file);
            QString sourcePath = QDir(fullPath).filePath(file);
            QString destinationPath = QDir(fullPath).filePath(info.fileName());

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