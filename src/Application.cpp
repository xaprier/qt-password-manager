#include "Application.hpp"

#include <qtranslator.h>

QTranslator Application::translator = QTranslator();

Application::Application(int &argc, char **argv, const QString &appName, const QString &appVersion, const QString &appOrg, const QString &appStyle)
    : QApplication(argc, argv) {
    this->setApplicationName(appName);
    this->setApplicationVersion(appVersion);
    this->setOrganizationName(appOrg);
    this->setStyleSheet(appStyle);
    this->setAppIcon();
    this->setAppLanguage();
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

void Application::setAppLanguage() {
    /** Localization */
    QLocale locale = QLocale::system();
    switch (locale.language()) {
        case QLocale::Turkish:
            if (translator.load(":/translations/translation_tr.qm")) {
                Logger::log_static(LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__, QObject::tr("Loaded language Turkish").toStdString());
            }
            break;
        case QLocale::German:
            if (translator.load(":/translations/translation_de.qm")) {
                Logger::log_static(LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__, QObject::tr("Loaded language German").toStdString());
            }
            break;
        case QLocale::English:
            break;
            // no need to install translator for application wrote in English
    }
    installTranslator(&translator);
}

void Application::setAppIcon() {
    setWindowIcon(QIcon(":/icons/xpwm.png"));
}