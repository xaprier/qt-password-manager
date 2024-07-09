#include "JSONHandler.hpp"

#include "JSONHandlerException.hpp"

JSONHandler::JSONHandler(const QString &fileFullPath, const QString &master_password, QObject *parent) : QObject(parent),
                                                                                                         m_settings(std::make_unique<QSettings>("xaprier", "Password Manager", this)),
                                                                                                         m_wrapper(std::make_unique<Cipher>(this)),
                                                                                                         m_password(master_password),
                                                                                                         m_fileFullPath(fileFullPath) {
    if (!this->decryptJSON()) throw JSONHandlerException("JSONHandler init error");
}

JSONHandler::~JSONHandler() {
    if (!this->encryptJSON()) Logger::log_static(LoggingLevel::WARNING, __LINE__, __PRETTY_FUNCTION__, "JSONHandler deinit error. Maybe file cannot be encrypted?");
}

bool JSONHandler::decryptJSON() {
    QByteArray encrypted;
    if (!this->readFile(m_fileFullPath, encrypted)) {
        Logger::log_static(LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__, QObject::tr("Cannot read file: %1").arg(m_fileFullPath).toStdString());
        return false;
    }

    m_decrypted = m_wrapper->decryptAES(m_password.toUtf8(), encrypted);
    QJsonParseError error{};
    m_json = QJsonDocument::fromJson(m_decrypted, &error);

    if (m_json.isNull()) {
        Logger::log_static(LoggingLevel::WARNING, __LINE__, __PRETTY_FUNCTION__, QObject::tr("Failed to parse JSON: %1").arg(error.errorString()).toStdString());
        return false;
    }

    return true;
}

bool JSONHandler::encryptJSON() {
    if (m_deleted) {
        Logger::log_static(LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__, QObject::tr("Will not encrypt because of file deleted").toStdString());
        return true;
    }

    QString filePath = m_fileFullPath;
    if (m_nameChanged) {
        Logger::log_static(LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__, QObject::tr("Encrypted filename change detected").toStdString());
        auto newName = m_json.object()["name"].toString();
        // update file name in m_fileFullPath
        QFileInfo info(m_fileFullPath);
        filePath = info.absolutePath() + "/" + newName + ".enc";
    }

    auto last = m_json.toJson();
    auto encrypted = m_wrapper->encryptAES(m_password.toUtf8(), last);
    if (!this->writeFile(filePath, encrypted)) {
        Logger::log_static(LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__, QObject::tr("Cannot write file %1").arg(filePath).toStdString());
        return false;
    }

    // write file is successful, if nameChanged we can delete old file.
    if (m_nameChanged) {
        QFile oldFile(m_fileFullPath);
        if (oldFile.exists()) {
            if (!oldFile.remove()) {
                Logger::log_static(LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__, QObject::tr("Failed to remove old file: ").arg(m_fileFullPath).toStdString());
            } else {
                Logger::log_static(LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__, QObject::tr("Old file removed: ").arg(m_fileFullPath).toStdString());
            }
        }
    }

    return true;
}

bool JSONHandler::readFile(QString filename, QByteArray &data) const {
    QFile file(filename);

    if (!file.open(QFile::ReadOnly)) {
        Logger::log_static(LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__, QObject::tr("Cannot open file: ").arg(file.errorString()).toStdString());
        return false;
    }

    data = file.readAll();
    file.close();

    return true;
}

bool JSONHandler::writeFile(QString filename, QByteArray &data) const {
    QFile file(filename);

    if (!file.open(QFile::WriteOnly)) {
        Logger::log_static(LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__, QObject::tr("Cannot open file: ").arg(file.errorString()).toStdString());
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
    if (m_json.isNull()) throw JSONHandlerException(QObject::tr("Decrypted JSON is not valid"));
    if (!m_json.object().contains("datas")) throw JSONHandlerException(QObject::tr("Invalid JSON format. Required area not found."));
    QJsonArray datas = m_json.object()["datas"].toArray();
    return datas;
}

const QString JSONHandler::name() const {
    if (m_json.isNull()) throw JSONHandlerException(QObject::tr("Decrypted JSON is not valid"));
    if (!m_json.object().contains("name")) throw JSONHandlerException(QObject::tr("Invalid JSON format. Required area not found."));
    return m_json.object()["name"].toString();
}

void JSONHandler::setName(const QString &name) {
    if (m_json.isNull()) throw JSONHandlerException(QObject::tr("Decrypted JSON is not valid"));
    QJsonObject jsonObj = m_json.object();
    if (!jsonObj.contains("name")) throw JSONHandlerException(QObject::tr("Invalid JSON format. Required area not found."));
    jsonObj["name"] = QJsonValue(name);
    m_json.setObject(jsonObj);
    m_nameChanged = true;
}

void JSONHandler::setPlatforms(const QJsonArray &platforms) {
    if (m_json.isNull()) throw JSONHandlerException(QObject::tr("Decrypted JSON is not valid"));
    QJsonObject jsonObj = m_json.object();
    if (!jsonObj.contains("datas")) throw JSONHandlerException(QObject::tr("Invalid JSON format. Required area not found."));
    jsonObj["datas"] = QJsonValue(platforms);
    m_json.setObject(jsonObj);
}

void JSONHandler::setMasterPassword(const QString &master_password) {
    this->m_password = master_password;
}

const bool JSONHandler::passwordSameAs(const QString &password) const {
    return password == m_password;
}