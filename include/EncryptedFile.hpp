#ifndef ENCRYPTEDFILE_HPP
#define ENCRYPTEDFILE_HPP

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>
#include <QtGlobal>

#include "Logger.hpp"

class EncryptedFile : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(EncryptedFile)
  public:
    EncryptedFile(const QString &fileName, QObject *parent = nullptr) : QObject(parent) {
        QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        QDir().mkpath(appDataPath);  // Ensure the directory exists
        m_file = new QFile(appDataPath + "/" + fileName + ".enc");
        Logger::log_static(appDataPath.toStdString() + "/" + fileName.toStdString() + ".enc");
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