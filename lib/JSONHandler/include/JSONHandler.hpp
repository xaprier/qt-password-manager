#ifndef JSONHANDLER_HPP
#define JSONHANDLER_HPP

#include <qglobal.h>
#include <qjsondocument.h>
#include <qobject.h>
#include <qsettings.h>

#include "Cipher.hpp"

class JSONHandler : public QObject {
    Q_DISABLE_COPY_MOVE(JSONHandler)
  public:
    explicit JSONHandler(const QString &master_password, QObject *parent = nullptr);
    ~JSONHandler();

    bool readFile(QString filename, QByteArray &data);
    bool writeFile(QString filename, QByteArray &data);

  protected:
    virtual bool decryptJSON(const QString &master_password);

  private:
    QJsonDocument m_json;
    QByteArray m_decrypted;
    QSettings m_settings;
    Cipher m_wrapper;
};

#endif  // JSONHANDLER_HPP