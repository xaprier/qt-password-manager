#ifndef CREATEENCRYPTEDFILE_HPP
#define CREATEENCRYPTEDFILE_HPP

#include <QObject>
#include <QtGlobal>

class CreateEncryptedFile : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(CreateEncryptedFile)
  public:
    explicit CreateEncryptedFile(const QString &fileName, const QString &masterPassword, QObject *base = nullptr);
    ~CreateEncryptedFile() override = default;
};

#endif  // CREATEENCRYPTEDFILE_HPP