#include <qapplication.h>
#include <qlocale.h>
#include <qobject.h>
#include <qtranslator.h>

#include <QTranslator>

#include "LoginDialog.hpp"
#include "MainWindow.hpp"

QTranslator translator;

void setAppLanguage(QApplication &app) {
    /** Localization */
    QLocale locale = QLocale::system();
    switch (locale.language()) {
        case QLocale::Turkish:
            if (translator.load(":/translations/translation_tr.qm")) {
                qDebug() << QObject::tr("Loaded language Turkish");
            }
            break;
        case QLocale::German:
            if (translator.load(":/translations/translation_de.qm")) {
                qDebug() << QObject::tr("Loaded language German");
            }
            break;
        case QLocale::English:
            break;
            // no need to install translator for application wrote in English
    }
    app.installTranslator(&translator);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    setAppLanguage(a);

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