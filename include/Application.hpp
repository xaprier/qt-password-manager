#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <QApplication>

class Application : public QApplication {
  public:
    Application(int &argc, char **argv, const QString &appName, const QString &appVersion, const QString &orgName, const QString &appStyle);
    ~Application();
    void setApplicationName(const QString &name);
    void setApplicationVersion(const QString &version);
    void setOrganizationName(const QString &name);
    void setStyleSheet(const QString &sheet);

  private:
    QString applicationName;
    QString applicationVersion;
    QString organizationName;
    QString styleSheet;
};

#endif  // APPLICATION_HPP