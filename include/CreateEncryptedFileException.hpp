#ifndef CREATEENCRYPTEDFILEEXCEPTION_HPP
#define CREATEENCRYPTEDFILEEXCEPTION_HPP

#include <QException>

class CreateEncryptedFileException : public QException {
  public:
    CreateEncryptedFileException(const QString &message) : m_message(message) {}  // NOLINT

    void raise() const override { throw *this; }
    [[nodiscard]] CreateEncryptedFileException *clone() const override { return new CreateEncryptedFileException(*this); }  // NOLINT

    [[nodiscard]] const QString &Message() const { return m_message; }

  private:
    QString m_message;
};

#endif  // CREATEENCRYPTEDFILEEXCEPTION_HPP