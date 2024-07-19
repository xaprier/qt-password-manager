#ifndef JSONHANDLER_HPP
#define JSONHANDLER_HPP

#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <memory>

#include "Cipher.hpp"
#include "Logger.hpp"

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
    void deleteFile() { m_deleted = true; }

    bool readFile(QString filename, QByteArray &data) const;
    bool writeFile(QString filename, QByteArray &data) const;
    static const QByteArray getDefaultJSON(const QString &fileName);

  protected:
    virtual bool decryptJSON();
    virtual bool encryptJSON();

  private:
    bool m_deleted = false;
    bool m_nameChanged = false;
    QJsonDocument m_json;
    QByteArray m_decrypted;
    QString m_fileFullPath;
    QString m_password;
    std::unique_ptr<Cipher> m_wrapper;
};

#endif  // JSONHANDLER_HPP