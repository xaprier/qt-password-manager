#ifndef CREATEDIALOG_HPP
#define CREATEDIALOG_HPP

#include <QComboBox>
#include <QDialog>

namespace Ui {
class CreateDialog;
}

class CreateDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(CreateDialog)
  public:
    explicit CreateDialog(QWidget *parent = nullptr);
    ~CreateDialog();
    inline const bool isCreated() { return m_isCreated; };

  private slots:
    void sl_accepted();
    void sl_rejected();
    void sl_checkBoxChanged(int state);
    void sl_generateClicked(bool checked);
    void sl_copyClicked(bool checked);

  private:
    bool m_isCreated = false;
    Ui::CreateDialog *m_ui;
};

#endif  // CREATEDIALOG_HPP
