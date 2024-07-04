#include "ImportDialog.hpp"

ImportDialog::ImportDialog(QWidget *parent) : QFileDialog(parent) {
    // enable multiple file selection
    this->setFileMode(QFileDialog::ExistingFiles);

    // filter with .enc files
    this->setNameFilter("Encrypted files (*.enc)");

    connect(this, &QFileDialog::filesSelected, this, &ImportDialog::onFilesSelected);
}

QStringList ImportDialog::getSelectedFiles() const {
    return m_selectedFiles;
}

void ImportDialog::onFilesSelected(const QStringList &files) {
    m_selectedFiles.clear();
    for (const QString &file : files) {
        if (file.endsWith(".enc", Qt::CaseInsensitive)) {
            m_selectedFiles.append(QDir::toNativeSeparators(file));
        }
    }
}