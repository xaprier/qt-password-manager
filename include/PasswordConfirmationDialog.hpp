#ifndef PASSWORDCONFIRMATIONDIALOG_H
#define PASSWORDCONFIRMATIONDIALOG_H

#include <QDialog>

#include "../design/ui_PasswordConfirmationDialog.h"

namespace Ui {
class PasswordConfirmationDialog;
}

class PasswordConfirmationDialog : public QDialog {
    Q_OBJECT

  public:
    explicit PasswordConfirmationDialog(QWidget *parent = nullptr);
    ~PasswordConfirmationDialog() override;
    [[nodiscard]] const QString getCurrentPassword() const { return this->m_ui->passwordLE->text(); }

  private slots:
    void sl_showPasswordStateChanged(int state);

  private:
    Ui::PasswordConfirmationDialog *m_ui;
};

#endif  // PASSWORDCONFIRMATIONDIALOG_H
