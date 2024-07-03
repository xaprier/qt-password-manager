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
            throw CreateEncryptedFileException("Failed to create directory: " + settingsFileInfo.absolutePath());
        }
    }

    // write encrypted into file
    QFile file(settingsFileInfo.absolutePath() + "/" + fileName + ".enc");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(encrypted);
        file.close();
        qDebug() << "Default JSON file created as encrypted successfully.";
    } else {
        throw CreateEncryptedFileException("File cannot open: " + file.fileName());
    }
}