#include "Auth.hpp"

#include "Cipher.hpp"

Auth::Auth(const QString &fileName, const QString &masterPassword, QObject *parent) : QObject(parent) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) return;
    auto encrypted = file.readAll();
    file.close();
    Cipher wrapper;
    auto decrypted = wrapper.decryptAES(masterPassword.toUtf8(), encrypted);
    bool isItJsonFile = this->isValidJson(decrypted);
    if (!decrypted.isEmpty() && !decrypted.isNull() && isItJsonFile) this->m_isAuthorized = true;
}

const bool Auth::isValidJson(const QByteArray &json) {
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(json, &parseError);
    return (parseError.error == QJsonParseError::NoError);
}