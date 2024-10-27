#include "OrganizationNameMigration.hpp"

void OrganizationNameMigration::Migrate() {
    // Path to old organization directory
    QString oldOrganizationPath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "/xaprier";

    // Check if the old directory exists
    QDir oldOrgDir(oldOrganizationPath);
    QDir oldAppDir(oldOrgDir.absolutePath() + QDir::separator() + APPNAME);

    // Check if the old directory contains ".enc" files
    QStringList filters;
    filters << "*.enc";  // Filter to find .enc files
    oldAppDir.setNameFilters(filters);
    QFileInfoList encryptedFiles = oldAppDir.entryInfoList();

    bool containsEncryptedFiles = !encryptedFiles.isEmpty();
    QString newAppDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    if (oldOrgDir.exists() && containsEncryptedFiles) {
        Logger::log_static(QObject::tr("Old organization data found at: %1").arg(oldOrganizationPath).toStdString());
        QMessageBox msgBox(QMessageBox::Icon::Question,
                           QObject::tr("Old Organization"),
                           QObject::tr("There is old organization data in your AppData location.\n",
                                       "Do you want the copy the encrypted files to new one and delete old directory?"),
                           QMessageBox::Button::Yes | QMessageBox::Button::No);
        if (msgBox.exec() == QMessageBox::Yes) {
            // Copy encrypted files to new location and delete old directory
            QString newAppDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

            QDir newDir(newAppDataPath);
            if (!newDir.exists()) {
                if (!newDir.mkpath(newAppDataPath)) {
                    throw MigrationException(QObject::tr("Failed to create directory: %1").arg(newAppDataPath));
                    return;
                }
            }

            for (const QFileInfo &fileInfo : encryptedFiles) {
                QString srcFilePath = fileInfo.absoluteFilePath();
                QString destFilePath = newAppDataPath + "/" + fileInfo.fileName();

                QFile::copy(srcFilePath, destFilePath);  // Copy each file
            }

            // Remove the old directory after copying files
            oldOrgDir.removeRecursively();
            Logger::log_static(QObject::tr("Encrypted files copied to: %1 and old directory removed.").arg(newAppDataPath).toStdString());
        }
    }
}