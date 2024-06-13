#include "MainWindow.hpp"

#include <qalgorithms.h>
#include <qpushbutton.h>
#include <qtoolbutton.h>

#include "../design/ui_MainWindow.h"
#include "MainWindowConnections.hpp"
#include "Platforms.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          m_ui(new Ui::MainWindow),
                                          m_connections(new MainWindowConnections(this)) {
    m_ui->setupUi(this);
    this->initPlatforms();
    this->initConnections();
}

MainWindow::~MainWindow() {
    delete m_ui;
    delete m_connections;
    qDeleteAll(this->platforms);
}

void MainWindow::initPlatforms() {
    this->platforms = {
        new Google(),
        new GitHub(),
        new GitLab(),
        new LinkedIn(),
        new Instagram(),
        new Reddit(),
        new Discord(),
        new Microsoft(),
        new Steam(),
        new Epic(),
        new Other()};

    for (const Platform *platform : platforms) {
        this->m_ui->platformCombo->addItem(platform->icon(), platform->name());
    }
}

void MainWindow::initConnections() {
    connect(this->m_ui->generateTB, &QToolButton::clicked, this->m_connections, &MainWindowConnections::sl_generateTBClicked);
    connect(this->m_ui->showPasswordCB, &QCheckBox::stateChanged, this->m_connections, &MainWindowConnections::sl_showPasswordCBStateChanged);
    connect(this->m_ui->createPB, &QPushButton::clicked, this->m_connections, &MainWindowConnections::sl_createPBClicked);
    connect(this->m_ui->deletePB, &QPushButton::clicked, this->m_connections, &MainWindowConnections::sl_deletePBClicked);
    connect(this->m_ui->platformsLW, &QListWidget::itemClicked, this->m_connections, &MainWindowConnections::sl_itemClickedLW);
}