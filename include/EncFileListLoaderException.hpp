#ifndef ENCFILELISTLOADEREXCEPTION_HPP
#define ENCFILELISTLOADEREXCEPTION_HPP

#include <QException>

class EncFileListLoaderException : public QException {
  public:
    EncFileListLoaderException(const QString &message) : m_message(message) {}  // NOLINT

    void raise() const override { throw *this; }
    [[nodiscard]] EncFileListLoaderException *clone() const override { return new EncFileListLoaderException(*this); }  // NOLINT

    [[nodiscard]] const QString &message() const { return m_message; }

  private:
    QString m_message;
};

#endif  // ENCFILELISTLOADEREXCEPTION_HPP