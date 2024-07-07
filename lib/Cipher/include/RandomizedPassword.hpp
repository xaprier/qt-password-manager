#ifndef RANDOMIZEDPASSWORD_HPP
#define RANDOMIZEDPASSWORD_HPP

#include <openssl/rand.h>

#include <QFile>
#include <QObject>
#include <QtGlobal>

class RandomizedPassword : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RandomizedPassword)
  public:
    enum CharacterSet {
        LOWERCASE = 1,
        UPPERCASE = 2,
        DIGITS = 4,
        SPECIAL = 8
    };
    Q_ENUM(CharacterSet)

    explicit RandomizedPassword(CharacterSet charSet, int charCount, QObject* parent = nullptr);
    ~RandomizedPassword();

    /**
     * @brief Get the randomized password which was created
     *
     * @return QByteArray
     */
    [[nodiscard]] inline const QByteArray getRandomizedPassword() { return m_randomizedPassword; }

  private:
    /**
     * @brief Get the char set according to CharacterSet
     *
     * @param charSet CharacterSet
     * @return QString
     */
    QString getCharacterSet(int charSet);

    /**
     * @brief generate password according to inputs
     *
     * @param length length of password
     * @param charset allowed charset
     * @return QByteArray
     */
    void generatePassword(int length, const QString& charset);

  private:
    QByteArray m_randomizedPassword;
};

#endif  // RANDOMIZEDPASSWORD_HPP
