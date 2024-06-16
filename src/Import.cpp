#include "Import.hpp"

#include <qdebug.h>
#include <qfile.h>
#include <qfileinfo.h>
#include <qmessagebox.h>
#include <qobject.h>
#include <qsettings.h>

#include "ImportDialog.hpp"

Import::Import(QObject *base) : QObject(base) {
    QSettings settings("xaprier", "Password Manager", this);
    QFileInfo info(settings.fileName());
    QString fullPath = info.absolutePath();

    ImportDialog dialog;
    if (dialog.exec() == QDialog::Accepted) {
        QStringList files = dialog.getSelectedFiles();
        for (const QString &file : files) {
            QFileInfo info(file);
            if (QFile::copy(file, fullPath + "/" + info.fileName())) {
                qDebug() << "Copied:" << file << "to" << fullPath;
            } else {
                QMessageBox::warning(nullptr, "Copy Error", "Failed to copy file: " + file);
            }
        }
    }
}

Import::~Import() {}