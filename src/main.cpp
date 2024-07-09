#include <qapplication.h>
#include <qlocale.h>
#include <qobject.h>
#include <qtranslator.h>

#include <QTranslator>

#include "Logger.hpp"
#include "LoginDialog.hpp"
#include "MainWindow.hpp"

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

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    setAppLanguage(a);
    setAppIcon(a);

    while (true) {
        LoginDialog login;
        int result = login.exec();
        if (result == QDialog::Accepted && login.isLogged()) {
            MainWindow window(login);
            window.show();
            a.exec();
        } else if (result == QDialog::Rejected)
            break;
    }
    return 0;
}