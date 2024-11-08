#include "CreateEncryptedFile.hpp"

#include <QDir>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

#include "Cipher.hpp"
#include "CreateEncryptedFileException.hpp"
#include "JSONHandler.hpp"

CreateEncryptedFile::CreateEncryptedFile(const QString &fileName, const QString &masterPassword, QObject *base) : QObject(base) {
    Cipher cipher;
    auto json = JSONHandler::getDefaultJSON(fileName);
    auto encrypted = cipher.encryptAES(masterPassword.toUtf8(), json);

    // get appdata path
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    // create path if not exists
    QDir dir(appDataPath);
    if (!dir.exists()) {
        if (!dir.mkpath(appDataPath)) {
            throw CreateEncryptedFileException(QObject::tr("Failed to create directory: %1").arg(appDataPath));
        }
    }

    // write encrypted into file
    QFile file(appDataPath + QDir::separator() + fileName + ".enc");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(encrypted);
        file.close();
        Logger::log_static(LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__, QObject::tr("Default JSON file created as encrypted successfully.").toStdString());
    } else {
        throw CreateEncryptedFileException(QObject::tr("File cannot open: %1").arg(file.fileName()));
    }
}