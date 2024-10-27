#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <QIcon>
#include <QJsonObject>
#include <QObject>
#include <QString>

class Platform : public QObject {
    Q_OBJECT
  public:
    explicit Platform(QString name, QIcon icon) : m_name(std::move(name)), m_icon(std::move(icon)) {}
    [[nodiscard]] const QIcon Icon() const { return m_icon; }
    [[nodiscard]] const QString Name() const { return m_name; }
    static std::unique_ptr<Platform> FromJson(const QJsonObject &object);

  private:
    QString m_name;
    QIcon m_icon;
};

// Platform base template
template <typename T>
class PlatformTemplate : public Platform {
  public:
    PlatformTemplate() : Platform(T::Name(), QIcon(T::IconPath())) {}
};

#endif  // PLATFORM_HPP