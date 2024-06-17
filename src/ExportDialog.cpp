#include "ExportDialog.hpp"

#include <qfiledialog.h>

#include <QPushButton>

ExportDialog::ExportDialog(QWidget *parent) : QFileDialog(parent) {}

ExportDialog::~ExportDialog() {}

QString ExportDialog::getSelectedDirectory() const {}

QStringList ExportDialog::getSelectedFiles() const {}