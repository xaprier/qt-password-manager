#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <QApplication>
#include <QIcon>

#include "Logger.hpp"

class Application : public QApplication {
  public:
    Application(int &argc, char **argv, const QString &appName, const QString &appVersion, const QString &orgName, const QString &appStyle);
    ~Application();
    void SetApplicationName(const QString &name);
    void SetApplicationVersion(const QString &version);
    void SetOrganizationName(const QString &name);
    void SetStyleSheet(const QString &sheet);

    static QTranslator translator;

  private:
    void _SetAppLanguage();
    void _SetAppIcon();
    QString m_applicationName;
    QString m_applicationVersion;
    QString m_organizationName;
    QString m_styleSheet;
};

#endif  // APPLICATION_HPP