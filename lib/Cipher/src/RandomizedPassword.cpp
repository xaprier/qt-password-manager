#include "RandomizedPassword.hpp"

#include <qobject.h>

#include "RandomizedPasswordException.hpp"

RandomizedPassword::RandomizedPassword(CharacterSet charSet, int charCount, QObject* parent)
    : QObject{parent} {
    QString charset = getCharacterSet(charSet);
    if (charset.isEmpty()) {
        throw RandomizedPasswordException(QObject::tr("No character sets selected."));
        return;
    }
    generatePassword(charCount, charset);
}

RandomizedPassword::~RandomizedPassword() {
}

QString RandomizedPassword::getCharacterSet(int charSet) {
    QString charset;
    if (charSet & LOWERCASE) {
        charset += "abcdefghijklmnopqrstuvwxyz";
    }
    if (charSet & UPPERCASE) {
        charset += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    }
    if (charSet & DIGITS) {
        charset += "0123456789";
    }
    if (charSet & SPECIAL) {
        charset += "!@#$%^&*()-_=+[]{}|;:,.<>?";
    }
    return charset;
}

void RandomizedPassword::generatePassword(int length, const QString& charset) {
    QByteArray password;
    unsigned char buffer[length];       // NOLINT
    if (!RAND_bytes(buffer, length)) {  // NOLINT
        throw RandomizedPasswordException(QObject::tr("Failed to generate random bytes."));
        return;
    }

    for (int i = 0; i < length; ++i) {
        password.append(charset[buffer[i] % charset.size()].toLatin1());
    }

    this->m_randomizedPassword = password;
}