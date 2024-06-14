#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <qglobal.h>

#include <QMainWindow>
#include <memory>

#include "../design/ui_MainWindow.h"
#include "JSONHandler.hpp"
#include "Platform.hpp"

namespace Ui {
class MainWindow;
}

class MainWindowConnections;  // Forward decleration
class LoginDialog;            // Forward decleration
class MainWindow : public QMainWindow {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(MainWindow)
  public:
    explicit MainWindow(const LoginDialog &dialog, QWidget *parent = nullptr);
    ~MainWindow();
    friend class MainWindowConnections;  //* allow m_ui reach

  private:
    void initPlatforms();
    void initConnections();
    void loadPlatforms();

  private:
    std::unique_ptr<JSONHandler> m_jsonHandler;
    QList<Platform *> m_platforms;
    Ui::MainWindow *m_ui;
    MainWindowConnections *m_connections;
};

#endif  // MAINWINDOW_HPP
