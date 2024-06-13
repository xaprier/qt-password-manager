#ifndef MAINWINDOWCONNECTIONS_HPP
#define MAINWINDOWCONNECTIONS_HPP

#include <qglobal.h>
#include <qobject.h>

#include <QListWidgetItem>
#include <QObject>

class MainWindow;
/**
 * @brief Creating another class which provides signals and slots because of preventing code mess in MainWindow.
 */
class MainWindowConnections : public QObject {  // NOLINT
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(MainWindowConnections)
  public:
    friend class MainWindow;

  private:
    MainWindowConnections(QObject *object = nullptr) : QObject(object) {}
    ~MainWindowConnections() override = default;

  signals:
  private slots:
    void sl_generateTBClicked(bool checked);
    void sl_showPasswordCBStateChanged(int state);
    void sl_createPBClicked(bool checked);
    void sl_deletePBClicked(bool checked);
    void sl_itemClickedLW(QListWidgetItem *item);
};

#endif  // MAINWINDOWCONNECTIONS_HPP