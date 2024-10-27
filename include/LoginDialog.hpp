#ifndef LOGINDIALOG_HPP
#define LOGINDIALOG_HPP

#include <QDialog>
#include <QMessageBox>
#include <QStandardItemModel>

#include "MainWindow.hpp"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(LoginDialog)

  public:
    explicit LoginDialog(QWidget* parent = nullptr);
    ~LoginDialog();

    const bool IsLogged() { return m_logged; }

    friend class MainWindow;

  private slots:
    void sl_Accepted();
    void sl_Rejected();
    void sl_NewClicked(bool checked);
    void sl_CheckBoxChanged(int state);
    void sl_ImportClicked(bool checked);
    void sl_ExportClicked(bool checked);
    void sl_UpdateClicked(bool checked);

  private:
    bool _verifyPassword(const QString& file, const QString& password);
    inline void _setLogged(bool logged) { this->m_logged = logged; }

  private:
    QString m_filePath;
    QString m_masterPassword;
    bool m_logged = false;
    Ui::LoginDialog* m_ui;
};

#endif  // LOGINDIALOG_HPP
