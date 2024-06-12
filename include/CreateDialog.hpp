#ifndef CREATEDIALOG_HPP
#define CREATEDIALOG_HPP

#include <qcombobox.h>

#include <QDialog>

namespace Ui {
class CreateDialog;
}

class CreateDialog : public QDialog {
    Q_OBJECT

  public:
    explicit CreateDialog(QWidget *parent = nullptr);
    ~CreateDialog();
    inline const bool isCreated() { return m_isCreated; };

  private slots:
    void sl_accepted();
    void sl_rejected();

  private:
    bool m_isCreated = false;
    Ui::CreateDialog *m_ui;
};

#endif  // CREATEDIALOG_HPP
