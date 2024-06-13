#ifndef RANDOMIZEDPASSWORDEXCEPTION_HPP
#define RANDOMIZEDPASSWORDEXCEPTION_HPP

#include <qexception.h>

class RandomizedPasswordException : public QException {
  public:
    RandomizedPasswordException(const QString &message) : m_message(message) {}  // NOLINT

    void raise() const override { throw *this; }
    [[nodiscard]] RandomizedPasswordException *clone() const override { return new RandomizedPasswordException(*this); }  // NOLINT

    [[nodiscard]] const QString &message() const { return m_message; }

  private:
    QString m_message;
};

#endif  // RANDOMIZEDPASSWORDEXCEPTION_HPP