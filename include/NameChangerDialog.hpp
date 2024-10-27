#ifndef NAMECHANGERDIALOG_HPP
#define NAMECHANGERDIALOG_HPP

#include <QDialog>

#include "../design/ui_NameChangerDialog.h"

namespace Ui {
class NameChangerDialog;
}

class NameChangerDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(NameChangerDialog)

  public:
    explicit NameChangerDialog(QWidget *parent = nullptr);
    ~NameChangerDialog();
    [[nodiscard]] const QString GetEnteredName() const { return this->m_ui->nameLE->text(); }
    [[nodiscard]] const QString GetCurrentPassword() const { return this->m_ui->currentPasswordLE->text(); }

  private slots:
    void sl_ShowPasswordCheckStateChanged(int state);

  private:
    Ui::NameChangerDialog *m_ui;
};

#endif  // NAMECHANGERDIALOG_HPP
