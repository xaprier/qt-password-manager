#ifndef JSONHANDLEREXCEPTION_HPP
#define JSONHANDLEREXCEPTION_HPP

#include <QException>

class JSONHandlerException : public QException {
  public:
    JSONHandlerException(const QString &message) : m_message(message) {}  // NOLINT

    void raise() const override { throw *this; }
    [[nodiscard]] JSONHandlerException *clone() const override { return new JSONHandlerException(*this); }

    [[nodiscard]] const QString &message() const { return m_message; }

  private:
    QString m_message;
};

#endif  // JSONHANDLEREXCEPTION_HPP