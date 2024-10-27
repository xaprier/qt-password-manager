#ifndef MIGRATIONEXCEPTION_HPP
#define MIGRATIONEXCEPTION_HPP

#include <QException>

class MigrationException : public QException {
  public:
    MigrationException(const QString &message) : m_message(message) {}  // NOLINT

    void raise() const override { throw *this; }
    [[nodiscard]] MigrationException *clone() const override { return new MigrationException(*this); }  // NOLINT

    [[nodiscard]] const QString &Message() const { return m_message; }

  private:
    QString m_message;
};

#endif  // MIGRATIONEXCEPTION_HPP