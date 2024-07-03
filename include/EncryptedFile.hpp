#ifndef ENCRYPTEDFILE_HPP
#define ENCRYPTEDFILE_HPP

#include <qfile.h>
#include <qfileinfo.h>
#include <qglobal.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qsettings.h>

class EncryptedFile : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(EncryptedFile)
  public:
    EncryptedFile(const QString &fileName, QObject *parent = nullptr) : QObject(parent) {
        QSettings settings("xaprier", "Password Manager", this);
        QFileInfo info(settings.fileName());
        QString fullPath = info.absolutePath();
        m_file = new QFile(fullPath + "/" + fileName + ".enc");
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