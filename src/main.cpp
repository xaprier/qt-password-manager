#include <qapplication.h>
#include <qdialog.h>

#include <iostream>

#include "LoginDialog.hpp"
#include "MainWindow.hpp"
#include "RandomizedPasswordDialog.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
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