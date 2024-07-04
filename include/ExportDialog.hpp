#ifndef EXPORTDIALOG_HPP
#define EXPORTDIALOG_HPP

#include <QDebug>
#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>

#include "MultiSelectionBox.hpp"

class ExportDialog : public QFileDialog {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ExportDialog)
  public:
    explicit ExportDialog(QStringList files, QWidget *parent = nullptr);
    ~ExportDialog() override;
    [[nodiscard]] QString getSelectedDirectory() const;
    [[nodiscard]] QStringList getSelectedFiles() const;

  private:
    QStringList m_selectedFiles;
    MultiSelectionBox *m_Files;
    QLabel *m_Label;
};

#endif  // EXPORTDIALOG_HPP
