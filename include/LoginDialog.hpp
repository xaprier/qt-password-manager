#ifndef LOGINDIALOG_HPP
#define LOGINDIALOG_HPP

#include <qglobal.h>

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(LoginDialog)

  public:
    explicit LoginDialog(QWidget* parent = nullptr);
    ~LoginDialog();

    const bool isLogged() { return m_logged; }

  private slots:
    void sl_accepted();
    void sl_rejected();

  private:
    bool verifyPassword(const QString& file, const QString& password);
    inline void setLogged(bool logged) { this->m_logged = logged; }

  private:
    bool m_logged = false;
    Ui::LoginDialog* m_ui;
};

#endif  // LOGINDIALOG_HPP
