#include <qobject.h>

#include <iostream>

#include "Cipher.hpp"
#include "LoggingLevel.hpp"

QByteArray getPrivateKey() {
    QByteArray testPrivateKey;
    QFile file("private.pem");
    if (!file.open(QFile::ReadOnly)) {
        Logger::log_static(LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__, QObject::tr("Cant open file: %1").arg(file.errorString()).toStdString());
        return testPrivateKey;
    }
    testPrivateKey = file.readAll();

    return testPrivateKey;
}

QByteArray getPublicKey() {
    QByteArray testPublicKey;
    QFile file("public.pem");
    if (!file.open(QFile::ReadOnly)) {
        Logger::log_static(LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__, QObject::tr("Cant open file: %1").arg(file.errorString()).toStdString());
        return testPublicKey;
    }
    testPublicKey = file.readAll();

    return testPublicKey;
}

void testRSA() {
    Logger::log_static(LoggingLevel::TESTING, __LINE__, __PRETTY_FUNCTION__, "Testing RSA...");
    QByteArray testPrivateKey = getPrivateKey();
    QByteArray testPublicKey = getPublicKey();

    Cipher cWrapper;
    RSA* publicKey = cWrapper.getPublicKey(testPublicKey);
    RSA* privateKey = cWrapper.getPrivateKey(testPrivateKey);

    QByteArray plain = "The man in black fled into the desert and gunslinger followed...";
    QByteArray encrypted = cWrapper.encryptRSA(publicKey, plain);
    QByteArray decrypted = cWrapper.decryptRSA(privateKey, encrypted);
    Logger::log_static(LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__, plain.toStdString());
    Logger::log_static(LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__, encrypted.toBase64().toStdString());
    Logger::log_static(LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__, decrypted.toStdString());
    cWrapper.freeRSAKey(publicKey);
    cWrapper.freeRSAKey(privateKey);
}

void testAES() {
    Logger::log_static(LoggingLevel::TESTING, __LINE__, __PRETTY_FUNCTION__, "Testing AES...");
    Cipher cWrapper;
    QString password = "password26";
    QByteArray plain = "The man in black fled into the desert and gunslinger followed...";
    QByteArray encrypted = cWrapper.encryptAES(password.toUtf8(), plain);
    QByteArray decrypted = cWrapper.decryptAES(password.toUtf8(), encrypted);
    Logger::log_static(LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__, plain.toStdString());
    Logger::log_static(LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__, encrypted.toBase64().toStdString());
    Logger::log_static(LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__, decrypted.toStdString());
}

bool readFile(QString filename, QByteArray& data) {
    QFile file(filename);

    if (!file.open(QFile::ReadOnly)) {
        Logger::log_static(LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__, QObject::tr("Cant open file: %1").arg(file.errorString()).toStdString());
        return false;
    }

    data = file.readAll();
    file.close();

    return true;
}

bool writeFile(QString filename, QByteArray& data) {
    QFile file(filename);

    if (!file.open(QFile::WriteOnly)) {
        Logger::log_static(LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__, QObject::tr("Cant open file: %1").arg(file.errorString()).toStdString());
        return false;
    }

    file.write(data);
    file.close();

    return true;
}

int main(int argc, char* argv[]) {
    testAES();
    testRSA();
    std::cout << "Cipher\n";
}