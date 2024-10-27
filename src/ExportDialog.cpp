#include "ExportDialog.hpp"

ExportDialog::ExportDialog(QStringList files, QWidget *parent) : QFileDialog(parent), m_SelectedFiles(files), m_Files(new MultiSelectionBox(this)), m_Label(new QLabel(this)) {
    // Enable only directory mode
    setFileMode(QFileDialog::Directory);
    setOption(QFileDialog::ShowDirsOnly, true);
    setOption(QFileDialog::DontUseNativeDialog, true);  // we need qt layout

    foreach (QString file, files) {
        // remove absolute path and add to m_Files combobox
        QFileInfo fileInfo(file);
        QString fileName = fileInfo.fileName();  // Extracts just the file name
        m_Files->addItem(fileName);
    }

    m_Label->setText(tr("Select files to export"));

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
        layout->addWidget(m_Label, 0, 0);
        layout->addWidget(m_Files, 0, 1);
    }

    for (int i = 0; i < moved_items.count(); i++) {
        layout->addItem(moved_items[i].first,
                        moved_items[i].second[0],
                        moved_items[i].second[1],
                        moved_items[i].second[2],
                        moved_items[i].second[3]);
    }
}

ExportDialog::~ExportDialog() {}

QString ExportDialog::GetSelectedDirectory() const {
    return selectedFiles().isEmpty() ? QString() : selectedFiles().first();
}

QStringList ExportDialog::GetSelectedFiles() const {
    auto selectedFileNames = this->m_Files->SelectedItems();
    // return filtered "QStringList m_selectedFiles" with selectedFileNames with ends alg.
    QStringList filteredFiles;

    for (const QString &file : m_SelectedFiles) {
        QFileInfo fileInfo(file);
        QString fileName = fileInfo.fileName();

        if (selectedFileNames.contains(fileName)) {
            filteredFiles.append(file);
        }
    }

    return filteredFiles;
}