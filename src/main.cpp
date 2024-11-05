#include "Application.hpp"
#include "Config.hpp"
#include "LoginDialog.hpp"
#include "MainWindow.hpp"
#include "OrganizationNameMigration.hpp"

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
    Application app(argc, argv, PROJECT_NAME, PROJECT_VERSION, PROJECT_ORGANIZATION, getQSS());
    OrganizationNameMigration migration;
    while (true) {
        LoginDialog login;
        int result = login.exec();
        if (result == QDialog::Accepted && login.IsLogged()) {
            MainWindow window(login);
            window.show();
            app.exec();
        } else if (result == QDialog::Rejected)
            break;
    }
    return 0;
}