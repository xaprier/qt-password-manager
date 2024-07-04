#include "Export.hpp"

Export::Export(QObject *base) : QObject(base) {
    QSettings settings("xaprier", "Password Manager", this);
    QFileInfo info(settings.fileName());
    QString fullPath = info.absolutePath();

    // get .enc file list from path
    QDir directory(fullPath);
    QStringList encFiles = directory.entryList(QStringList() << "*.enc", QDir::Files);

    // get export directory
    ExportDialog dialog(encFiles);
    if (dialog.exec() == QDialog::Accepted) {
        QStringList files = dialog.getSelectedFiles();
        QString path = dialog.getSelectedDirectory();

        for (const QString &file : files) {
            QFileInfo info(file);
            QString sourcePath = fullPath + QDir::separator() + file;
            QString destinationPath = path + QDir::separator() + info.fileName();

            // Check if source file exists
            if (!QFile::exists(sourcePath)) {
                qDebug() << "Source file does not exist:" << sourcePath;
                QMessageBox::warning(nullptr, "Copy Error", "Source file does not exist: " + sourcePath);
                continue;
            }

            // Check if destination file already exists
            if (QFile::exists(destinationPath)) {
                qDebug() << "Destination file already exists:" << destinationPath;
                QMessageBox::warning(nullptr, "Copy Error", "Destination file already exists: " + destinationPath);
                continue;
            }

            // Attempt to copy file
            if (QFile::copy(sourcePath, destinationPath)) {
                qDebug() << "Copied:" << sourcePath << "to" << destinationPath;
            } else {
                qDebug() << "Failed to copy file:" << sourcePath << "to" << destinationPath;
                QMessageBox::warning(nullptr, "Copy Error", "Failed to copy file '" + sourcePath + "' to '" + destinationPath + "'");
            }
        }
    }
}