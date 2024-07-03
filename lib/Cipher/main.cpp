#include <iostream>

#include "Cipher.hpp"

QByteArray getPrivateKey() {
    QByteArray testPrivateKey;
    QFile file("private.pem");
    if (!file.open(QFile::ReadOnly)) {
        qCritical() << "Cant open file: " << file.errorString();
        return testPrivateKey;
    }
    testPrivateKey = file.readAll();

    return testPrivateKey;
}

QByteArray getPublicKey() {
    QByteArray testPublicKey;
    QFile file("public.pem");
    if (!file.open(QFile::ReadOnly)) {
        qCritical() << "Cant open file: " << file.errorString();
        return testPublicKey;
    }
    testPublicKey = file.readAll();

    return testPublicKey;
}

void testRSA() {
    qDebug() << "Testing RSA...";
    QByteArray testPrivateKey = getPrivateKey();
    QByteArray testPublicKey = getPublicKey();

    Cipher cWrapper;
    RSA* publicKey = cWrapper.getPublicKey(testPublicKey);
    RSA* privateKey = cWrapper.getPrivateKey(testPrivateKey);

    QByteArray plain = "The man in black fled into the desert and gunslinger followed...";
    QByteArray encrypted = cWrapper.encryptRSA(publicKey, plain);
    QByteArray decrypted = cWrapper.decryptRSA(privateKey, encrypted);
    qDebug() << plain;
    qDebug() << encrypted.toBase64();
    qDebug() << decrypted;
    cWrapper.freeRSAKey(publicKey);
    cWrapper.freeRSAKey(privateKey);
}

void testAES() {
    qDebug() << "Testing AES...";
    Cipher cWrapper;
    QString password = "password26";
    QByteArray plain = "The man in black fled into the desert and gunslinger followed...";
    QByteArray encrypted = cWrapper.encryptAES(password.toUtf8(), plain);
    QByteArray decrypted = cWrapper.decryptAES(password.toUtf8(), encrypted);
    qDebug() << plain;
    qDebug() << encrypted.toBase64();
    qDebug() << decrypted;
}

bool readFile(QString filename, QByteArray& data) {
    QFile file(filename);

    if (!file.open(QFile::ReadOnly)) {
        qCritical() << "Cant open file: " << file.errorString();
        return false;
    }

    data = file.readAll();
    file.close();

    return true;
}

bool writeFile(QString filename, QByteArray& data) {
    QFile file(filename);

    if (!file.open(QFile::WriteOnly)) {
        qCritical() << "Cant open file: " << file.errorString();
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