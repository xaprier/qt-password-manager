#include "Cipher.hpp"

Cipher::Cipher(QObject *parent)
    : QObject{parent} {
    initialize();
}

Cipher::~Cipher() {
    finalize();
}

RSA *Cipher::getPublicKey(QByteArray &data) {
    const char *publicKeyStr = data.constData();
    BIO *bio = BIO_new_mem_buf((void *)publicKeyStr, -1);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

    RSA *rsaPublicKey = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL);

    if (!rsaPublicKey) {
        qCritical() << "Could not load public key" << ERR_error_string(ERR_get_error(), NULL);
    }

    BIO_free(bio);

    return rsaPublicKey;
}

RSA *Cipher::getPublicKey(QString filename) {
    QByteArray data = readFile(filename);
    return getPublicKey(data);
}

RSA *Cipher::getPrivateKey(QByteArray &data) {
    const char *privateKeyStr = data.constData();

    BIO *bio = BIO_new_mem_buf((void *)privateKeyStr, -1);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

    RSA *rsaPrivateKey = PEM_read_bio_RSAPrivateKey(bio, NULL, NULL, NULL);

    if (!rsaPrivateKey) {
        qCritical() << "Could not load private key" << ERR_error_string(ERR_get_error(), NULL);
    }

    BIO_free(bio);

    return rsaPrivateKey;
}

RSA *Cipher::getPrivateKey(QString filename) {
    QByteArray data = readFile(filename);
    return getPrivateKey(data);
}

QByteArray Cipher::encryptRSA(RSA *key, QByteArray &data) {
    QByteArray buffer;
    int dataSize = data.length();
    const unsigned char *str = (const unsigned char *)data.constData();

    int rsaLen = RSA_size(key);
    unsigned char *ed = (unsigned char *)malloc(rsaLen);

    int resultLen = RSA_public_encrypt(dataSize, str, ed, key, PADDING);
    if (resultLen == -1) {
        qCritical() << "Could not encrypt: " << ERR_error_string(ERR_get_error(), NULL);
        free(ed);
        return buffer;
    }

    buffer = QByteArray(reinterpret_cast<char *>(ed), resultLen);

    free(ed);
    return buffer;
}

QByteArray Cipher::decryptRSA(RSA *key, QByteArray &data) {
    QByteArray buffer;
    const unsigned char *encryptedData = (const unsigned char *)data.constData();

    int rsaLen = RSA_size(key);
    unsigned char *decryptedBin = (unsigned char *)malloc(rsaLen);

    int resultLen = RSA_private_decrypt(rsaLen, encryptedData, decryptedBin, key, PADDING);
    if (resultLen == -1) {
        qCritical() << "Could not decrypt: " << ERR_error_string(ERR_get_error(), NULL);
        free(decryptedBin);
        return buffer;
    }

    buffer = QByteArray(reinterpret_cast<const char *>(decryptedBin), resultLen);
    free(decryptedBin);
    return buffer;
}

QByteArray Cipher::encryptAES(QByteArray passphrase, QByteArray &data) {
    QByteArray msalt = randomBytes(SALTSIZE);
    int rounds = 1;
    unsigned char *key = new unsigned char[KEYSIZE];
    unsigned char *iv = new unsigned char[IVSIZE];

    const unsigned char *salt = (const unsigned char *)msalt.constData();
    const unsigned char *password = (const unsigned char *)passphrase.constData();
    int i = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), salt, password, passphrase.length(), rounds, key, iv);

    if (i != KEYSIZE) {
        qCritical() << "EVP_BytesToKey() error: " << ERR_error_string(ERR_get_error(), NULL);
        delete[] key;
        delete[] iv;
        return QByteArray();
    }

    EVP_CIPHER_CTX *en = EVP_CIPHER_CTX_new();
    EVP_CIPHER_CTX_init(en);

    if (!EVP_EncryptInit_ex(en, EVP_aes_256_cbc(), NULL, key, iv)) {
        qCritical() << "EVP_EncryptInit_ex() failed: " << ERR_error_string(ERR_get_error(), NULL);
        EVP_CIPHER_CTX_free(en);
        delete[] key;
        delete[] iv;
        return QByteArray();
    }

    char *input = data.data();
    int len = data.size();

    int c_len = len + AES_BLOCK_SIZE, f_len = 0;

    unsigned char *cipherText = (unsigned char *)malloc(c_len);

    if (!EVP_EncryptInit_ex(en, NULL, NULL, NULL, NULL)) {
        qCritical() << "EVP_EncryptInit_ex() failed: " << ERR_error_string(ERR_get_error(), NULL);
        EVP_CIPHER_CTX_free(en);
        delete[] key;
        delete[] iv;
        free(cipherText);
        return QByteArray();
    }

    // May have to repeat this for large files
    if (!EVP_EncryptUpdate(en, cipherText, &c_len, (unsigned char *)input, len)) {
        qCritical() << "EVP_EncryptUpdate() failed: " << ERR_error_string(ERR_get_error(), NULL);
        EVP_CIPHER_CTX_free(en);
        delete[] key;
        delete[] iv;
        free(cipherText);
        return QByteArray();
    }

    if (!EVP_EncryptFinal(en, cipherText + c_len, &f_len)) {
        qCritical() << "EVP_EncryptFinal() failed: " << ERR_error_string(ERR_get_error(), NULL);
        EVP_CIPHER_CTX_free(en);
        delete[] key;
        delete[] iv;
        free(cipherText);
        return QByteArray();
    }

    len = c_len + f_len;

    EVP_CIPHER_CTX_cleanup(en);

    QByteArray encrypted = QByteArray(reinterpret_cast<char *>(cipherText), len);
    QByteArray finished;
    finished.append("Salted__");
    finished.append(msalt);
    finished.append(encrypted);

    delete[] iv;
    delete[] key;
    free(cipherText);
    EVP_CIPHER_CTX_free(en);
    return finished;
}

QByteArray Cipher::decryptAES(QByteArray passphrase, QByteArray &data) {
    QByteArray msalt;
    if (QString(data.mid(0, 8)) == "Salted__") {
        msalt = data.mid(8, 8);
        data = data.mid(16);  // start position to 16
    } else {
        qWarning() << "Could not load salt from data!";
        msalt = randomBytes(SALTSIZE);
    }

    int rounds = 1;
    unsigned char *key = new unsigned char[KEYSIZE];
    unsigned char *iv = new unsigned char[IVSIZE];

    const unsigned char *salt = (const unsigned char *)msalt.constData();
    const unsigned char *password = (const unsigned char *)passphrase.constData();

    int i = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), salt, password, passphrase.length(), rounds, key, iv);

    if (i != KEYSIZE) {
        qCritical() << "EVP_BytesToKey() error: " << ERR_error_string(ERR_get_error(), NULL);
        delete[] key;
        delete[] iv;
        return QByteArray();
    }

    EVP_CIPHER_CTX *dec = EVP_CIPHER_CTX_new();
    EVP_CIPHER_CTX_init(dec);

    if (!EVP_DecryptInit_ex(dec, EVP_aes_256_cbc(), NULL, key, iv)) {
        qCritical() << "EVP_DecryptInit_ex failed: " << ERR_error_string(ERR_get_error(), NULL);
        EVP_CIPHER_CTX_free(dec);
        delete[] key;
        delete[] iv;
        return QByteArray();
    }

    char *input = data.data();
    int len = data.size();

    int p_len = len, f_len = 0;
    unsigned char *plain = (unsigned char *)malloc(p_len + AES_BLOCK_SIZE);

    // May have to do this multiple times for large data
    if (!EVP_DecryptUpdate(dec, plain, &p_len, (unsigned char *)input, len)) {
        qCritical() << "EVP_DecryptUpdate failed: " << ERR_error_string(ERR_get_error(), NULL);
        free(plain);
        EVP_CIPHER_CTX_free(dec);
        delete[] key;
        delete[] iv;
        return QByteArray();
    }

    if (!EVP_DecryptFinal_ex(dec, plain + p_len, &f_len)) {
        qCritical() << "EVP_DecryptFinal_ex failed: " << ERR_error_string(ERR_get_error(), NULL);
        free(plain);
        EVP_CIPHER_CTX_free(dec);
        delete[] key;
        delete[] iv;
        return QByteArray();
    }

    len = p_len + f_len;

    QByteArray decrypted = QByteArray(reinterpret_cast<char *>(plain), len);

    EVP_CIPHER_CTX_cleanup(dec);
    EVP_CIPHER_CTX_free(dec);
    free(plain);
    delete[] key;
    delete[] iv;

    return decrypted;
}

QByteArray Cipher::randomBytes(int size) {
    unsigned char *arr = new unsigned char[size];
    RAND_bytes(arr, size);

    QByteArray buffer = QByteArray(reinterpret_cast<char *>(arr), size);

    delete[] arr;
    return buffer;
}

void Cipher::freeRSAKey(RSA *key) {
    RSA_free(key);
}

void Cipher::initialize() {
    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();
}

void Cipher::finalize() {
    EVP_cleanup();
    ERR_free_strings();
}

QByteArray Cipher::readFile(QString filename) {
    QByteArray data;
    QFile file(filename);
    if (!file.open(QFile::ReadOnly)) {
        qCritical() << file.errorString();
        return data;
    }

    data = file.readAll();
    file.close();
    return data;
}

void Cipher::writeFile(QString filename, QByteArray &data) {
    QFile file(filename);
    ;
    if (!file.open(QFile::ReadWrite)) {
        qCritical() << "Cant open file: " << file.errorString();
        return;
    }

    file.write(data);
    file.close();
}
