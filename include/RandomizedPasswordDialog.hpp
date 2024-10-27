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

    const QByteArray GetGeneratedPassword() { return m_generatedPassword; }

  private slots:
    void sl_GenerateClicked(bool clicked);
    void sl_CheckBoxToggled(bool toggle);
    void sl_ShowPassword(int state);
    void sl_CopyClicked(bool checked);
    void sl_ValueChanged(int value);

  private:
    void _InitConnections();

  private:
    QByteArray m_generatedPassword;
    Ui::RandomizedPasswordDialog *m_ui;
};

#endif  // RANDOMIZEDPASSWORDDIALOG_HPP
