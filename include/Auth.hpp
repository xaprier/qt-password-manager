#ifndef AUTH_HPP
#define AUTH_HPP

#include <QJsonDocument>
#include <QJsonParseError>
#include <QObject>

class Auth : public QObject {
    Q_OBJECT
  public:
    explicit Auth(const QString &file, const QString &masterPassword, QObject *parent = nullptr);
    inline const bool IsAuthorized() { return m_isAuthorized; }

  private:
    const bool _IsValidJson(const QByteArray &json);

  private:
    bool m_isAuthorized = false;
};

#endif  // AUTH_HPP