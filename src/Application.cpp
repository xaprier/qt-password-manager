#include "Application.hpp"

Application::Application(int &argc, char **argv, const QString &appName, const QString &appVersion, const QString &appOrg, const QString &appStyle)
    : QApplication(argc, argv) {
    this->setApplicationName(appName);
    this->setApplicationVersion(appVersion);
    this->setOrganizationName(appOrg);
    this->setStyleSheet(appStyle);
}

Application::~Application() {
}

void Application::setApplicationName(const QString &name) {
    applicationName = name;
    QApplication::setApplicationName(name);
}

void Application::setApplicationVersion(const QString &version) {
    applicationVersion = version;
    QApplication::setApplicationVersion(version);
}

void Application::setOrganizationName(const QString &name) {
    organizationName = name;
    QApplication::setOrganizationName(name);
}

void Application::setStyleSheet(const QString &sheet) {
    styleSheet = sheet;
    QApplication::setStyleSheet(sheet);
}