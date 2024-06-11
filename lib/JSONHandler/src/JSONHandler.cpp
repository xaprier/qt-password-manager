#include "JSONHandler.hpp"

#include <qexception.h>
#include <qfileinfo.h>
#include <qjsondocument.h>
#include <qobject.h>
#include <qsettings.h>

#include "JSONHandlerException.hpp"

JSONHandler::JSONHandler(const QString &master_password, QObject *parent) : QObject(parent),
                                                                            m_settings(QSettings("xaprier", "Password Manager", this)),
                                                                            m_wrapper(Cipher(this)) {
    if (!this->decryptJSON(master_password)) {
        throw JSONHandlerException("JSONHandler init error");
    }
}

JSONHandler::~JSONHandler() {
}

bool JSONHandler::decryptJSON(const QString &master_password) {
    // get path
    QFileInfo info(m_settings.fileName());
    QString file = info.absolutePath() + "/data.enc";

    QByteArray encrypted;
    if (!this->readFile(file, encrypted)) {
        qDebug() << "Cannot read file: " << file;
        return false;
    }

    auto decrypted = m_wrapper.decryptAES(master_password.toUtf8(), encrypted);
    QJsonParseError error{};
    m_json = QJsonDocument::fromJson(decrypted, &error);

    if (m_json.isNull()) {
        qWarning() << "Failed to parse JSON:" << error.errorString();
        return false;
    }

    return true;
}

bool JSONHandler::readFile(QString filename, QByteArray &data) {
    QFile file(filename);

    if (!file.open(QFile::ReadOnly)) {
        qCritical() << "Cant open file: " << file.errorString();
        return false;
    }

    data = file.readAll();
    file.close();

    return true;
}

bool JSONHandler::writeFile(QString filename, QByteArray &data) {
    QFile file(filename);

    if (!file.open(QFile::WriteOnly)) {
        qCritical() << "Cant open file: " << file.errorString();
        return false;
    }

    file.write(data);
    file.close();

    return true;
}