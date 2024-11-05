#ifndef MAINWINDOWCONNECTIONS_HPP
#define MAINWINDOWCONNECTIONS_HPP

#include <QClipboard>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QObject>

#include "AboutDialog.hpp"
#include "MainWindow.hpp"

/**
 * @brief Creating another class which provides signals and slots because of preventing code mess in MainWindow.
 */
class MainWindowConnections : public QObject {  // NOLINT
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(MainWindowConnections)
  public:
    friend class MainWindow;

  private:
    MainWindowConnections(MainWindow *base, Ui::MainWindow *ui, QObject *object = nullptr) : QObject(object), m_base(base), m_ui(ui) {}
    ~MainWindowConnections() override = default;
    Ui::MainWindow *m_ui{};
    MainWindow *m_base{};

  signals:

  private slots:
    void sl_GenerateTBClicked(bool checked);
    void sl_ShowPasswordCBStateChanged(int state);
    void sl_CreatePBClicked(bool checked);
    void sl_UpdatePBClicked(bool checked);
    void sl_DeletePBClicked(bool checked);
    void sl_ItemClickedLW(QListWidgetItem *item);
    void sl_ActionChangeNameTriggered(bool checked);
    void sl_ActionChangeMasterPasswordTriggered(bool checked);
    void sl_ActionDeleteTriggered(bool checked);
    void sl_ActionAboutTriggered(bool checked);
    void sl_CopyClicked(bool checked);
};

#endif  // MAINWINDOWCONNECTIONS_HPP