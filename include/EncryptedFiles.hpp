#ifndef ENCRYPTEDFILES_HPP
#define ENCRYPTEDFILES_HPP

#include <qalgorithms.h>
#include <qdir.h>
#include <qfile.h>
#include <qfileinfo.h>
#include <qglobal.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qsettings.h>

#include "EncryptedFile.hpp"

class EncryptedFiles : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(EncryptedFiles)
  public:
    EncryptedFiles(QObject *parent = nullptr) : QObject(parent) {
        QSettings settings("xaprier", "Password Manager", this);
        QFileInfo info(settings.fileName());
        QString fullPath = info.absolutePath();
        QDir encryptedFilesPath(fullPath);

        // Get all files with .enc extension
        QStringList encFiles = encryptedFilesPath.entryList(QStringList() << "*.enc", QDir::Files);

        // Add each .enc file to the files list
        for (const QString &fileName : encFiles) {
            QString filePath = encryptedFilesPath.absoluteFilePath(fileName);
            auto *encFile = new EncryptedFile(QFileInfo(filePath).baseName());
            m_files.append(encFile);
        }
    }

    ~EncryptedFiles() override {
        qDeleteAll(m_files);
        m_files.clear();
    }

    [[nodiscard]] const bool contains(const QString &fileName) const {
        for (const EncryptedFile *file : m_files) {
            if (file->fileName() == fileName) {
                return true;
            }
        }
        return false;
    }

    bool deleteFile(const QString &fileName) {
        for (const EncryptedFile *file : m_files) {
            if (file->fileName() == fileName) {
                file->file()->moveToTrash();
                return true;
            }
        }
        return false;
    }

  private:
    QList<EncryptedFile *> m_files;
};

#endif  // ENCRYPTEDFILES_HPP