#ifndef ENCRYPTEDFILES_HPP
#define ENCRYPTEDFILES_HPP

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QObject>
#include <QtAlgorithms>

#include "EncryptedFile.hpp"
#include "Logger.hpp"

class EncryptedFiles : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(EncryptedFiles)
  public:
    EncryptedFiles(QObject *parent = nullptr) : QObject(parent) {
        QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        QDir dir(appDataPath);
        if (!dir.exists()) {
            if (!dir.mkpath(appDataPath)) {
                throw CreateEncryptedFileException(QObject::tr("Failed to create directory: %1").arg(appDataPath));
            }
        }

        Logger::log_static(appDataPath.toStdString());

        // Get all files with .enc extension
        QStringList encFiles = dir.entryList(QStringList() << "*.enc", QDir::Files);

        // Add each .enc file to the files list
        for (const QString &fileName : encFiles) {
            QString filePath = dir.absoluteFilePath(fileName);
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
            if (file->FileName() == fileName) {
                return true;
            }
        }
        return false;
    }

    bool DeleteFile(const QString &fileName) {
        for (const EncryptedFile *file : m_files) {
            if (file->FileName() == fileName) {
                file->File()->moveToTrash();
                return true;
            }
        }
        return false;
    }

  private:
    QList<EncryptedFile *> m_files;
};

#endif  // ENCRYPTEDFILES_HPP