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
                qDebug() << tr("Source file does not exist: %1").arg(sourcePath);
                QMessageBox::warning(nullptr, tr("Copy Error"), tr("Source file does not exist: %1").arg(sourcePath));
                continue;
            }

            // Check if destination file already exists
            if (QFile::exists(destinationPath)) {
                qDebug() << tr("Destination file already exists: %1").arg(destinationPath);
                QMessageBox::warning(nullptr, tr("Copy Error"), tr("Destination file already exists: %1").arg(destinationPath));
                continue;
            }

            // Attempt to copy file
            if (QFile::copy(sourcePath, destinationPath)) {
                qDebug() << tr("Copied '%1' to '%2'").arg(sourcePath, destinationPath);
            } else {
                qDebug() << tr("Failed to copy file '%1' to '%2'").arg(sourcePath, destinationPath);
                QMessageBox::warning(nullptr, tr("Copy Error"), tr("Failed to copy file '%1' to '%2'").arg(sourcePath, destinationPath));
            }
        }
    }
}