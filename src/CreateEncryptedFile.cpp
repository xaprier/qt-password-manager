#include "CreateEncryptedFile.hpp"

#include <qexception.h>

#include <QDir>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>

#include "Cipher.hpp"
#include "CreateEncryptedFileException.hpp"
#include "JSONHandler.hpp"

CreateEncryptedFile::CreateEncryptedFile(const QString &fileName, const QString &masterPassword, QObject *base) : QObject(base) {
    Cipher cipher;
    auto json = JSONHandler::getDefaultJSON(fileName);
    auto encrypted = cipher.encryptAES(masterPassword.toUtf8(), json);

    // get QSettings path
    QString settingsPath = QSettings("xaprier", "Password Manager").fileName();
    QFileInfo settingsFileInfo(settingsPath);

    // create path if not exists
    QDir dir(settingsFileInfo.absolutePath());
    if (!dir.exists()) {
        if (!dir.mkpath(settingsFileInfo.absolutePath())) {
            throw CreateEncryptedFileException(QObject::tr("Failed to create directory: %1").arg(settingsFileInfo.absolutePath()));
        }
    }

    // write encrypted into file
    QFile file(settingsFileInfo.absolutePath() + QDir::separator() + fileName + ".enc");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(encrypted);
        file.close();
        qDebug() << QObject::tr("Default JSON file created as encrypted successfully.");
    } else {
        throw CreateEncryptedFileException(QObject::tr("File cannot open: %1").arg(file.fileName()));
    }
}