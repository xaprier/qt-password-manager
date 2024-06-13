#ifndef RANDOMIZEDPASSWORDDIALOG_HPP
#define RANDOMIZEDPASSWORDDIALOG_HPP

#include <qglobal.h>

#include <QDialog>

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

  private:
    void initConnections();

  private:
    QByteArray m_generatedPassword;
    Ui::RandomizedPasswordDialog *m_ui;
};

#endif  // RANDOMIZEDPASSWORDDIALOG_HPP
