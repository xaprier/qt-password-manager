#include "MainWindow.hpp"

#include <qaction.h>
#include <qalgorithms.h>
#include <qapplication.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qtoolbutton.h>

#include "JSONHandler.hpp"
#include "LoginDialog.hpp"
#include "MainWindowConnections.hpp"
#include "Platform.hpp"
#include "Platforms.hpp"

MainWindow::MainWindow(const LoginDialog &dialog, QWidget *parent) : QMainWindow(parent),
                                                                     m_ui(new Ui::MainWindow),
                                                                     m_connections(new MainWindowConnections(this, m_ui)) {
    m_jsonHandler = std::make_unique<JSONHandler>(dialog.m_filePath, dialog.m_masterPassword);

    m_ui->setupUi(this);
    this->initPlatforms();
    this->initConnections();
    this->loadPlatforms();
}

MainWindow::~MainWindow() {
    delete m_ui;
    delete m_connections;
    qDeleteAll(this->m_platforms);
}

void MainWindow::initPlatforms() {
    this->m_platforms = {
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

    for (const Platform *platform : m_platforms) {
        this->m_ui->platformCombo->addItem(platform->icon(), platform->name());
    }
}

void MainWindow::initConnections() {
    connect(this->m_ui->generateTB, &QToolButton::clicked, this->m_connections, &MainWindowConnections::sl_generateTBClicked);
    connect(this->m_ui->showPasswordCB, &QCheckBox::stateChanged, this->m_connections, &MainWindowConnections::sl_showPasswordCBStateChanged);
    connect(this->m_ui->createPB, &QPushButton::clicked, this->m_connections, &MainWindowConnections::sl_createPBClicked);
    connect(this->m_ui->deletePB, &QPushButton::clicked, this->m_connections, &MainWindowConnections::sl_deletePBClicked);
    connect(this->m_ui->updatePB, &QPushButton::clicked, this->m_connections, &MainWindowConnections::sl_updatePBClicked);
    connect(this->m_ui->platformsLW, &QListWidget::itemClicked, this->m_connections, &MainWindowConnections::sl_itemClickedLW);
    connect(this->m_ui->actionChange_Name, &QAction::triggered, this->m_connections, &MainWindowConnections::sl_actionChangeNameTriggered);
    connect(this->m_ui->actionChange_Master_Password, &QAction::triggered, this->m_connections, &MainWindowConnections::sl_actionChangeMasterPasswordTriggered);
}

void MainWindow::loadPlatforms() {
    this->m_ui->platformsLW->clear();
    auto array = m_jsonHandler->platforms();
    for (const auto &item : array) {
        if (item.isObject()) {
            auto object = item.toObject();
            auto name = object["name"].toString();
            auto platform = Platform::fromJson(object);
            // add platform to QListWidget
            if (platform) {
                auto *listItem = new QListWidgetItem(platform->icon(), name);
                this->m_ui->platformsLW->addItem(listItem);
            }
        }
    }
}
