#include <qapplication.h>
#include <qdialog.h>

#include <iostream>

#include "LoginDialog.hpp"
#include "RandomizedPasswordDialog.hpp"
#include "MainWindow.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    // LoginDialog d;
    // while (!d.isLogged()) {
    //     if (d.exec() == QDialog::Rejected) return 0;
    // }
    // now its logged, create mainwindow with the decrypted file
    return a.exec();
}