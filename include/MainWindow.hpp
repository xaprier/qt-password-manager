#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <qglobal.h>

#include <QMainWindow>

#include "MainWindowConnections.hpp"
#include "Platform.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(MainWindow)
  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    friend class MainWindowConnections;  //* allow m_ui reach

  private:
    void initPlatforms();
    void initConnections();

  private:
    QList<Platform *> platforms;
    Ui::MainWindow *m_ui;
    MainWindowConnections *m_connections;
};

#endif  // MAINWINDOW_HPP
