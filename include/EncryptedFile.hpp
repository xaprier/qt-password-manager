#ifndef ENCRYPTEDFILE_HPP
#define ENCRYPTEDFILE_HPP

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>
#include <QtGlobal>

#include "CreateEncryptedFileException.hpp"
#include "Logger.hpp"

class EncryptedFile : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(EncryptedFile)
  public:
    EncryptedFile(const QString &fileName, QObject *parent = nullptr) : QObject(parent) {
        QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        QDir dir(appDataPath);
        if (!dir.exists()) {
            if (!dir.mkpath(appDataPath)) {
                throw CreateEncryptedFileException(QObject::tr("Failed to create directory: %1").arg(appDataPath));
            }
        }
        m_file = new QFile(appDataPath + QDir::separator() + fileName + ".enc");
        Logger::log_static(m_file->fileName().toStdString());
        m_fileInfo = QFileInfo(*m_file);
        m_fileName = QFileInfo(fileName).baseName();
    }

    ~EncryptedFile() override { delete m_file; }
    [[nodiscard]] const QString fileName() const { return m_fileName; }
    [[nodiscard]] QFile *file() const { return m_file; }
    [[nodiscard]] const QFileInfo fileInfo() const { return m_fileInfo; }

  private:
    QString m_fileName;
    QFile *m_file;
    QFileInfo m_fileInfo;
};

#endif  // ENCRYPTEDFILE_HPP