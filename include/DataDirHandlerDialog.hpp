#ifndef DATADIRHANDLER_HPP
#define DATADIRHANDLER_HPP

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
    explicit DataDirHandlerDialog(QWidget* parent = nullptr) : QDialog(parent), m_DataDirs(Singleton<DataDirs>::Instance()) {
        QHBoxLayout* buttonLayout = new QHBoxLayout();
        QVBoxLayout* layout = new QVBoxLayout(this);

        m_ListView = new QListView(this);
        m_Model = new QStringListModel(this);
        m_ListView->setModel(m_Model);

        m_AddButton = new QPushButton(QObject::tr("Add Directory"), this);
        m_UpdateButton = new QPushButton(QObject::tr("Update Directory"), this);
        m_DeleteButton = new QPushButton(QObject::tr("Delete Directory"), this);

        layout->addWidget(m_ListView);
        buttonLayout->addWidget(m_AddButton);
        buttonLayout->addWidget(m_UpdateButton);
        buttonLayout->addWidget(m_DeleteButton);
        layout->addLayout(buttonLayout);

        connect(m_AddButton, &QPushButton::clicked, this, &DataDirHandlerDialog::OnAddDir);
        connect(m_UpdateButton, &QPushButton::clicked, this, &DataDirHandlerDialog::OnUpdateDir);
        connect(m_DeleteButton, &QPushButton::clicked, this, &DataDirHandlerDialog::OnDeleteDir);

        setLayout(layout);

        // Load the DataDirs
        UpdateModel();
    }

    ~DataDirHandlerDialog() {
    }

  private slots:
    void OnAddDir() {
        // Open a file dialog for selecting a directory
        QString dirPath = QFileDialog::getExistingDirectory(nullptr,
                                                            QObject::tr("Select Directory"),
                                                            QString(),
                                                            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

        // Check if the user selected a directory
        if (!dirPath.isEmpty()) {
            // Prompt the user to confirm if they want to add the selected directory
            auto reply = QMessageBox::question(nullptr,
                                               QObject::tr("Add Directory"),
                                               QObject::tr("Do you want to add this directory:\n%1").arg(dirPath),
                                               QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                // User accepted to add the directory
                DataDir dataDir(dirPath);
                m_DataDirs.AddDataDir(dataDir);
                UpdateModel();
            }
        }
    }

    void OnUpdateDir() {
        // elevate no item selection
        QModelIndex currentIndex = m_ListView->currentIndex();
        if (!currentIndex.isValid()) {
            QMessageBox::warning(nullptr, QObject::tr("No Selection"), QObject::tr("No items selected, please select an item first."));
            return;
        }
        int selected = m_ListView->currentIndex().row();

        // Open a file dialog for selecting a directory
        QString dirPath = QFileDialog::getExistingDirectory(nullptr,
                                                            QObject::tr("Select Directory"),
                                                            QString(),
                                                            QFileDialog::DontResolveSymlinks);
        // Check if the user selected a directory
        if (!dirPath.isEmpty()) {
            // Prompt the user to confirm if they want to add the selected directory
            QMessageBox msgBox;
            msgBox.setWindowTitle(QObject::tr("Update Directory"));
            msgBox.setTextFormat(Qt::RichText);
            msgBox.setText(QObject::tr("Do you want to update the directory?<br><b>New: %1</b><br><b>Old: %2</b>")
                               .arg(m_DataDirs.GetDataDirs().at(selected).GetPath(), dirPath));
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            auto reply = static_cast<QMessageBox::StandardButton>(msgBox.exec());

            if (reply == QMessageBox::Yes) {
                // User accepted to add the directory
                DataDir dataDir(dirPath);
                m_DataDirs.UpdateDataDir(selected, dirPath);
                UpdateModel();
            }
        }
    }

    void OnDeleteDir() {
        QModelIndex currentIndex = m_ListView->currentIndex();
        if (currentIndex.isValid()) {
            int selected = m_ListView->currentIndex().row();
            auto reply = QMessageBox::question(nullptr,
                                               QObject::tr("Delete Directory"),
                                               QObject::tr("Do you want to delete directory:\n%1").arg(m_DataDirs.GetDataDirs().at(selected).GetPath()),
                                               QMessageBox::Button::Yes | QMessageBox::Button::No);
            if (reply == QMessageBox::StandardButton::Yes) {
                m_DataDirs.RemoveDataDir(currentIndex.row());
                UpdateModel();
            }
        }
    }

  private:
    void UpdateModel() {
        QStringList dirList;
        for (const auto& dataDir : m_DataDirs.GetDataDirs()) {
            dirList << dataDir.GetPath();
        }
        m_Model->setStringList(dirList);
    }

    QListView* m_ListView;
    QStringListModel* m_Model;
    QPushButton* m_AddButton;
    QPushButton* m_DeleteButton;
    QPushButton* m_UpdateButton;
    DataDirs& m_DataDirs;
};

#endif  // DATADIRHANDLER_HPP