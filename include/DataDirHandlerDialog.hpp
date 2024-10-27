#ifndef DATADIRHANDLER_HPP
#define DATADIRHANDLER_HPP

#include <QDebug>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QListView>
#include <QMessageBox>
#include <QPushButton>
#include <QStringListModel>
#include <QVBoxLayout>
#include <QWidget>

#include "DataDirs.hpp"
#include "singleton.hpp"

class DataDirHandlerDialog : public QDialog {
    Q_OBJECT

  public:
    explicit DataDirHandlerDialog(QWidget* parent = nullptr) : QDialog(parent), m_dataDirs(Singleton<DataDirs>::Instance()) {
        QHBoxLayout* buttonLayout = new QHBoxLayout();
        QVBoxLayout* layout = new QVBoxLayout(this);

        m_listView = new QListView(this);
        m_model = new QStringListModel(this);
        m_listView->setModel(m_model);

        m_addButton = new QPushButton(QObject::tr("Add Directory"), this);
        m_updateButton = new QPushButton(QObject::tr("Update Directory"), this);
        m_deleteButton = new QPushButton(QObject::tr("Delete Directory"), this);

        layout->addWidget(m_listView);
        buttonLayout->addWidget(m_addButton);
        buttonLayout->addWidget(m_updateButton);
        buttonLayout->addWidget(m_deleteButton);
        layout->addLayout(buttonLayout);

        connect(m_addButton, &QPushButton::clicked, this, &DataDirHandlerDialog::sl_OnAddDir);
        connect(m_updateButton, &QPushButton::clicked, this, &DataDirHandlerDialog::sl_OnUpdateDir);
        connect(m_deleteButton, &QPushButton::clicked, this, &DataDirHandlerDialog::sl_OnDeleteDir);

        setLayout(layout);

        // Load the DataDirs
        _UpdateModel();
    }

    ~DataDirHandlerDialog() {
    }

  private slots:
    void sl_OnAddDir() {
        // Open a file dialog for selecting a directory
        QString dirPath = QFileDialog::getExistingDirectory(nullptr,
                                                            QObject::tr("Select Directory"),
                                                            QString(),
                                                            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        QDir dir(dirPath);
        // Check if the user selected a directory
        if (!dirPath.isEmpty() && dir.exists()) {
            // Prompt the user to confirm if they want to add the selected directory
            auto reply = QMessageBox::question(nullptr,
                                               QObject::tr("Add Directory"),
                                               QObject::tr("Do you want to add this directory:\n%1").arg(dirPath),
                                               QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                // User accepted to add the directory
                DataDir dataDir(dirPath);
                m_dataDirs.AddDataDir(dataDir);
                _UpdateModel();
            }
        }
    }

    void sl_OnUpdateDir() {
        // elevate no item selection
        QModelIndex currentIndex = m_listView->currentIndex();
        if (!currentIndex.isValid()) {
            QMessageBox::warning(nullptr, QObject::tr("No Selection"), QObject::tr("No items selected, please select an item first."));
            return;
        }
        int selected = m_listView->currentIndex().row();

        // Open a file dialog for selecting a directory
        QString dirPath = QFileDialog::getExistingDirectory(nullptr,
                                                            QObject::tr("Select Directory"),
                                                            QString(),
                                                            QFileDialog::DontResolveSymlinks);
        QDir dir(dirPath);
        // Check if the user selected a directory
        if (!dirPath.isEmpty() && dir.exists()) {
            // Prompt the user to confirm if they want to add the selected directory
            QMessageBox msgBox;
            msgBox.setWindowTitle(QObject::tr("Update Directory"));
            msgBox.setTextFormat(Qt::RichText);
            msgBox.setText(QObject::tr("Do you want to update the directory?<br><b>New: %1</b><br><b>Old: %2</b>")
                               .arg(m_dataDirs.GetDataDirs().at(selected).GetPath(), dirPath));
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            auto reply = static_cast<QMessageBox::StandardButton>(msgBox.exec());

            if (reply == QMessageBox::Yes) {
                // User accepted to add the directory
                DataDir dataDir(dirPath);
                m_dataDirs.UpdateDataDir(selected, dirPath);
                _UpdateModel();
            }
        }
    }

    void sl_OnDeleteDir() {
        QModelIndex currentIndex = m_listView->currentIndex();
        if (currentIndex.isValid()) {
            int selected = m_listView->currentIndex().row();
            auto reply = QMessageBox::question(nullptr,
                                               QObject::tr("Delete Directory"),
                                               QObject::tr("Do you want to delete directory:\n%1").arg(m_dataDirs.GetDataDirs().at(selected).GetPath()),
                                               QMessageBox::Button::Yes | QMessageBox::Button::No);
            if (reply == QMessageBox::StandardButton::Yes) {
                m_dataDirs.RemoveDataDir(currentIndex.row());
                _UpdateModel();
            }
        }
    }

  private:
    void _UpdateModel() {
        QStringList dirList;
        for (const auto& dataDir : m_dataDirs.GetDataDirs()) {
            dirList << dataDir.GetPath();
        }
        m_model->setStringList(dirList);
    }

    QListView* m_listView;
    QStringListModel* m_model;
    QPushButton* m_addButton;
    QPushButton* m_deleteButton;
    QPushButton* m_updateButton;
    DataDirs& m_dataDirs;
};

#endif  // DATADIRHANDLER_HPP