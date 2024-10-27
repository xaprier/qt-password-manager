#include "ImportDialog.hpp"

#include <qdialog.h>
#include <qmessagebox.h>
#include <qnamespace.h>
#include <qtoolbutton.h>

#include <QDebug>

#include "DataDirHandlerDialog.hpp"
#include "DataDirs.hpp"

ImportDialog::ImportDialog(QWidget *parent) : QFileDialog(parent), m_label(new QLabel(this)), m_dataDirSelectionBox(new QComboBox(this)), m_execDataDirHandlerDialogButton(new QToolButton(this)) {
    // enable multiple file selection
    this->setFileMode(QFileDialog::ExistingFiles);

    // filter with .enc files
    this->setNameFilter(tr("Encrypted files") + " (*.enc)");

    m_label->setText(tr("Select Data Directory to import"));
    this->_UpdateDataDirSelectionList();

    m_execDataDirHandlerDialogButton->setIcon(QIcon(":/icons/update.svg"));
    m_execDataDirHandlerDialogButton->setToolTip(QObject::tr("Add/Update/Delete Data Directories to search Encrypted Files"));

    // update current layout
    QList<QPair<QLayoutItem *, QList<int>>> moved_items;
    auto *layout = static_cast<QGridLayout *>(this->layout());
    for (int i = 0; i < layout->count(); i++) {
        int row, column, rowSpan, columnSpan;
        layout->getItemPosition(i, &row, &column, &rowSpan, &columnSpan);
        if (row >= 0) {
            QList<int> list;
            list << (row + 1) << column << rowSpan << columnSpan;
            moved_items << qMakePair(layout->takeAt(i), list);
            i--;  // takeAt has shifted the rest items
        }
    }

    // Insert the horizontal layout into the file dialog's layout
    if (layout) {
        layout->addWidget(m_label, 0, 0);
        layout->addWidget(m_dataDirSelectionBox, 0, 1);
        layout->addWidget(m_execDataDirHandlerDialogButton, 0, 2);
    }

    for (int i = 0; i < moved_items.count(); i++) {
        layout->addItem(moved_items[i].first,
                        moved_items[i].second[0],
                        moved_items[i].second[1],
                        moved_items[i].second[2],
                        moved_items[i].second[3]);
    }

    connect(this, &QFileDialog::filesSelected, this, &ImportDialog::sl_OnFilesSelected);
    connect(this->m_execDataDirHandlerDialogButton, &QToolButton::clicked, this, &ImportDialog::sl_OnToolButtonClicked);
    connect(this, &QDialog::accepted, this, &ImportDialog::sl_Accepted);
}

QStringList ImportDialog::GetSelectedFiles() const {
    return m_selectedFiles;
}

QString ImportDialog::GetSelectedDataDirectory() const {
    return this->m_dataDirSelectionBox->currentText();
}

void ImportDialog::sl_OnFilesSelected(const QStringList &files) {
    m_selectedFiles.clear();
    for (const QString &file : files) {
        if (file.endsWith(".enc", Qt::CaseInsensitive)) {
            m_selectedFiles.append(QDir::toNativeSeparators(file));
        } else {
            QMessageBox::warning(this, tr("Error"), tr("Invalid file type. Please select encrypted files ends with .enc"));
            return;
        }
    }
}

void ImportDialog::_UpdateDataDirSelectionList() {
    auto &dataDirs = Singleton<DataDirs>::Instance();
    m_dataDirSelectionBox->clear();
    m_dataDirSelectionBox->addItem("");
    for (const auto &dataDir : dataDirs.GetDataDirs()) {
        m_dataDirSelectionBox->addItem(dataDir.GetPath());
    }
}

void ImportDialog::sl_OnToolButtonClicked(bool clicked) {
    DataDirHandlerDialog dialog;
    dialog.exec();
    this->_UpdateDataDirSelectionList();
}

void ImportDialog::sl_Accepted() {
    if (this->m_selectedFiles.empty()) {
        QMessageBox::warning(this, tr("Error"), tr("No encrypted file selected. Please select an encrypted file."));
        return;
    }
}