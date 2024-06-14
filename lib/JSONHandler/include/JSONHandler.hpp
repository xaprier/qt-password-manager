#ifndef JSONHANDLER_HPP
#define JSONHANDLER_HPP

#include <qglobal.h>
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qobject.h>
#include <qsettings.h>

#include "Cipher.hpp"

class JSONHandler : public QObject {
    Q_DISABLE_COPY_MOVE(JSONHandler)
  public:
    explicit JSONHandler(const QString &fileFullPath, const QString &master_password, QObject *parent = nullptr);
    ~JSONHandler();

    [[nodiscard]] const QString name() const;
    [[nodiscard]] const QJsonArray platforms() const;
    [[nodiscard]] const bool passwordSameAs(const QString &password) const;

    void setName(const QString &name);
    void setPlatforms(const QJsonArray &platforms);
    void setMasterPassword(const QString &master_password);

    bool readFile(QString filename, QByteArray &data) const;
    bool writeFile(QString filename, QByteArray &data) const;
    static const QByteArray getDefaultJSON(const QString &fileName);

  protected:
    virtual bool decryptJSON();
    virtual bool encryptJSON();

  private:
    bool nameChanged = false;
    QJsonDocument m_json;
    QByteArray m_decrypted;
    QString m_fileFullPath;
    QString m_password;
    QSettings m_settings;
    Cipher m_wrapper;
};

#endif  // JSONHANDLER_HPP