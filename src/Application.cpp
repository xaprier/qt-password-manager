#include "Application.hpp"

#include <qtranslator.h>

QTranslator Application::translator = QTranslator();

Application::Application(int &argc, char **argv, const QString &appName, const QString &appVersion, const QString &appOrg, const QString &appStyle)
    : QApplication(argc, argv) {
    this->SetApplicationName(appName);
    this->SetApplicationVersion(appVersion);
    this->SetOrganizationName(appOrg);
    this->SetStyleSheet(appStyle);
    this->_SetAppIcon();
    this->_SetAppLanguage();
}

Application::~Application() {
}

void Application::SetApplicationName(const QString &name) {
    m_applicationName = name;
    QApplication::setApplicationName(name);
}

void Application::SetApplicationVersion(const QString &version) {
    m_applicationVersion = version;
    QApplication::setApplicationVersion(version);
}

void Application::SetOrganizationName(const QString &name) {
    m_organizationName = name;
    QApplication::setOrganizationName(name);
}

void Application::SetStyleSheet(const QString &sheet) {
    m_styleSheet = sheet;
    QApplication::setStyleSheet(sheet);
}

void Application::_SetAppLanguage() {
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

void Application::_SetAppIcon() {
    setWindowIcon(QIcon(":/icons/xpwm.png"));
}