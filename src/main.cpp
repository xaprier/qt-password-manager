#include <qlocale.h>
#include <qobject.h>
#include <qtranslator.h>

#include <QTranslator>

#include "Application.hpp"
#include "Logger.hpp"
#include "LoginDialog.hpp"
#include "MainWindow.hpp"
#include "RandomizedPassword.hpp"

QTranslator translator;

void setAppLanguage(QApplication &app) {
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
    app.installTranslator(&translator);
}

void setAppIcon(QApplication &app) {
    app.setWindowIcon(QIcon(":/icons/xpwm.png"));
}

QString getQSS() {
    QFile styleFile(":/qss/style.qss");
    if (!styleFile.open(QFile::ReadOnly)) {
        Logger::log_static(LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__, QObject::tr("Style file cannot be opened").toStdString());
        return QString();
    }

    QString style(styleFile.readAll());
    return style;
}

int main(int argc, char *argv[]) {
    Application app(argc, argv, "XPwm", "1.0.1", "xaprier", getQSS());

    setAppLanguage(app);
    setAppIcon(app);

    while (true) {
        LoginDialog login;
        int result = login.exec();
        if (result == QDialog::Accepted && login.isLogged()) {
            MainWindow window(login);
            window.show();
            app.exec();
        } else if (result == QDialog::Rejected)
            break;
    }
    return 0;
}