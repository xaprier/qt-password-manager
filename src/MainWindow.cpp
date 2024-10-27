#include "MainWindow.hpp"

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
    this->_InitPlatforms();
    this->_InitConnections();
    this->_LoadPlatforms();
}

MainWindow::~MainWindow() {
    delete m_ui;
    qDeleteAll(this->m_platforms);
}

void MainWindow::_InitPlatforms() {
    this->m_platforms = {
        new Discord(),
        new Epic(),
        new GitHub(),
        new GitLab(),
        new Google(),
        new Instagram(),
        new LinkedIn(),
        new Microsoft(),
        new Reddit(),
        new Steam(),
        new Other()};

    for (const Platform *platform : m_platforms) {
        this->m_ui->platformCombo->addItem(platform->Icon(), platform->Name());
    }
}

void MainWindow::_InitConnections() {
    connect(this->m_ui->copyTB, &QToolButton::clicked, this->m_connections, &MainWindowConnections::sl_CopyClicked);
    connect(this->m_ui->generateTB, &QToolButton::clicked, this->m_connections, &MainWindowConnections::sl_GenerateTBClicked);
    connect(this->m_ui->showPasswordCB, &QCheckBox::stateChanged, this->m_connections, &MainWindowConnections::sl_ShowPasswordCBStateChanged);
    connect(this->m_ui->createPB, &QPushButton::clicked, this->m_connections, &MainWindowConnections::sl_CreatePBClicked);
    connect(this->m_ui->deletePB, &QPushButton::clicked, this->m_connections, &MainWindowConnections::sl_DeletePBClicked);
    connect(this->m_ui->updatePB, &QPushButton::clicked, this->m_connections, &MainWindowConnections::sl_UpdatePBClicked);
    connect(this->m_ui->platformsLW, &QListWidget::itemClicked, this->m_connections, &MainWindowConnections::sl_ItemClickedLW);
    connect(this->m_ui->actionChange_Name, &QAction::triggered, this->m_connections, &MainWindowConnections::sl_ActionChangeNameTriggered);
    connect(this->m_ui->actionChange_Master_Password, &QAction::triggered, this->m_connections, &MainWindowConnections::sl_ActionChangeMasterPasswordTriggered);
    connect(this->m_ui->actionDelete, &QAction::triggered, this->m_connections, &MainWindowConnections::sl_ActionDeleteTriggered);
}

void MainWindow::_LoadPlatforms() {
    this->m_ui->platformsLW->clear();
    auto array = m_jsonHandler->platforms();
    for (const auto &item : array) {
        if (item.isObject()) {
            auto object = item.toObject();
            auto name = object["name"].toString();
            auto platform = Platform::FromJson(object);
            // add platform to QListWidget
            if (platform) {
                auto *listItem = new QListWidgetItem(platform->Icon(), name);
                this->m_ui->platformsLW->addItem(listItem);
            }
        }
    }
}
