#include "JSONHandler.hpp"

#include <qexception.h>
#include <qfileinfo.h>
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonvalue.h>
#include <qobject.h>
#include <qsettings.h>

#include "JSONHandlerException.hpp"

JSONHandler::JSONHandler(const QString &fileFullPath, const QString &master_password, QObject *parent) : QObject(parent),
                                                                                                         m_settings(QSettings("xaprier", "Password Manager", this)),
                                                                                                         m_wrapper(Cipher(this)),
                                                                                                         m_password(master_password),
                                                                                                         m_fileFullPath(fileFullPath) {
    if (!this->decryptJSON()) throw JSONHandlerException("JSONHandler init error");
}

JSONHandler::~JSONHandler() {
    if (!this->encryptJSON()) qWarning() << "JSONHandler deinit error. Maybe file cannot be encrypted?";
}

bool JSONHandler::decryptJSON() {
    QByteArray encrypted;
    if (!this->readFile(m_fileFullPath, encrypted)) {
        qDebug() << "Cannot read file: " << m_fileFullPath;
        return false;
    }

    m_decrypted = m_wrapper.decryptAES(m_password.toUtf8(), encrypted);
    QJsonParseError error{};
    m_json = QJsonDocument::fromJson(m_decrypted, &error);

    if (m_json.isNull()) {
        qWarning() << "Failed to parse JSON:" << error.errorString();
        return false;
    }

    return true;
}

bool JSONHandler::encryptJSON() {
    qDebug() << "[JSONHandler] encryptJSON: " << m_fileFullPath << m_password.toUtf8() << m_json;
    if (m_deleted) {
        qDebug() << "[JSONHandler] encryptJSON: will not encrypt because of file deleted";
        return true;
    }

    QString filePath = m_fileFullPath;
    if (m_nameChanged) {
        qDebug() << "[JSONHandler] encryptJSON: nameChanged";
        auto newName = m_json.object()["name"].toString();
        // update file name in m_fileFullPath
        QFileInfo info(m_fileFullPath);
        filePath = info.absolutePath() + "/" + newName + ".enc";
    }
    qDebug() << "Path: " << filePath;

    auto last = m_json.toJson();
    auto encrypted = m_wrapper.encryptAES(m_password.toUtf8(), last);
    if (!this->writeFile(filePath, encrypted)) {
        qDebug() << "Cannot write file: " << filePath;
        return false;
    }

    // write file is successful, if nameChanged we can delete old file.
    if (m_nameChanged) {
        QFile oldFile(m_fileFullPath);
        if (oldFile.exists()) {
            if (!oldFile.remove()) {
                qDebug() << "Failed to remove old file:" << m_fileFullPath;
            } else {
                qDebug() << "Old file removed:" << m_fileFullPath;
            }
        }
    }

    return true;
}

bool JSONHandler::readFile(QString filename, QByteArray &data) const {
    QFile file(filename);

    if (!file.open(QFile::ReadOnly)) {
        qCritical() << "Cant open file: " << file.errorString();
        return false;
    }

    data = file.readAll();
    file.close();

    return true;
}

bool JSONHandler::writeFile(QString filename, QByteArray &data) const {
    QFile file(filename);

    if (!file.open(QFile::WriteOnly)) {
        qCritical() << "Cant open file: " << file.errorString();
        return false;
    }

    file.write(data);
    file.close();

    return true;
}

const QByteArray JSONHandler::getDefaultJSON(const QString &fileName) {
    QJsonObject jsonObject;
    jsonObject["name"] = fileName;
    jsonObject["datas"] = QJsonArray();

    QJsonDocument jsonDoc(jsonObject);
    return jsonDoc.toJson();
}

const QJsonArray JSONHandler::platforms() const {
    if (m_json.isNull()) throw JSONHandlerException("Decrypted JSON is not valid");
    if (!m_json.object().contains("datas")) throw JSONHandlerException("Invalid JSON format. Required area not found.");
    QJsonArray datas = m_json.object()["datas"].toArray();
    return datas;
}

const QString JSONHandler::name() const {
    if (m_json.isNull()) throw JSONHandlerException("Decrypted JSON is not valid");
    if (!m_json.object().contains("name")) throw JSONHandlerException("Invalid JSON format. Required area not found.");
    return m_json.object()["name"].toString();
}

void JSONHandler::setName(const QString &name) {
    if (m_json.isNull()) throw JSONHandlerException("Decrypted JSON is not valid");
    QJsonObject jsonObj = m_json.object();
    if (!jsonObj.contains("name")) throw JSONHandlerException("Invalid JSON format. Required area not found.");
    jsonObj["name"] = QJsonValue(name);
    m_json.setObject(jsonObj);
    m_nameChanged = true;
}

void JSONHandler::setPlatforms(const QJsonArray &platforms) {
    if (m_json.isNull()) throw JSONHandlerException("Decrypted JSON is not valid");
    QJsonObject jsonObj = m_json.object();
    if (!jsonObj.contains("datas")) throw JSONHandlerException("Invalid JSON format. Required area not found.");
    jsonObj["datas"] = QJsonValue(platforms);
    m_json.setObject(jsonObj);
}

void JSONHandler::setMasterPassword(const QString &master_password) {
    this->m_password = master_password;
}

const bool JSONHandler::passwordSameAs(const QString &password) const {
    return password == m_password;
}