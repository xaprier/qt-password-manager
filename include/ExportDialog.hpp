#ifndef EXPORTDIALOG_HPP
#define EXPORTDIALOG_HPP

#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>

#include "MultiSelectionBox.hpp"

// todo: make it singleton
// todo: should get files from DataDirs
class ExportDialog : public QFileDialog {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ExportDialog)
  public:
    explicit ExportDialog(QStringList files, QWidget *parent = nullptr);
    ~ExportDialog() override;
    [[nodiscard]] QString GetSelectedDirectory() const;
    [[nodiscard]] QStringList GetSelectedFiles() const;

  private:
    QStringList m_SelectedFiles;
    MultiSelectionBox *m_Files;
    QLabel *m_Label;
};

#endif  // EXPORTDIALOG_HPP
