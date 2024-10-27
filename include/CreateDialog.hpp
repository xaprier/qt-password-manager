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
    inline const bool IsCreated() { return m_isCreated; };

  private slots:
    void sl_Accepted();
    void sl_Rejected();
    void sl_CheckBoxChanged(int state);
    void sl_GenerateClicked(bool checked);
    void sl_CopyClicked(bool checked);

  private:
    bool m_isCreated = false;
    Ui::CreateDialog *m_ui;
};

#endif  // CREATEDIALOG_HPP
