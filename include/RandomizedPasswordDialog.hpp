#ifndef RANDOMIZEDPASSWORDDIALOG_HPP
#define RANDOMIZEDPASSWORDDIALOG_HPP

#include <QClipboard>
#include <QDialog>
#include <QMessageBox>

namespace Ui {
class RandomizedPasswordDialog;
}

class RandomizedPasswordDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RandomizedPasswordDialog)

  public:
    explicit RandomizedPasswordDialog(QWidget *parent = nullptr);
    ~RandomizedPasswordDialog() override;

    const QByteArray getGeneratedPassword() { return m_generatedPassword; }

  private slots:
    void sl_generateClicked(bool clicked);
    void sl_checkBoxToggled(bool toggle);
    void sl_showPassword(int state);
    void sl_copyClicked(bool checked);
    void sl_valueChanged(int value);

  private:
    void initConnections();

  private:
    QByteArray m_generatedPassword;
    Ui::RandomizedPasswordDialog *m_ui;
};

#endif  // RANDOMIZEDPASSWORDDIALOG_HPP
