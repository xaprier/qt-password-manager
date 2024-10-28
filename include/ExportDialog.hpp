#ifndef EXPORTDIALOG_HPP
#define EXPORTDIALOG_HPP

#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>

#include "MultiSelectionBox.hpp"
#include "singleton.hpp"

class ExportDialog : public QFileDialog {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ExportDialog)
  public:
    friend Singleton<ExportDialog>;
    [[nodiscard]] QString GetSelectedDirectory() const;
    [[nodiscard]] QStringList GetSelectedFiles() const;
    void SetFiles(const QStringList &files);

  private:
    explicit ExportDialog(QStringList files, QWidget *parent = nullptr);
    ~ExportDialog() override;

  private:
    QStringList m_SelectedFiles;
    MultiSelectionBox *m_Files;
    QLabel *m_Label;
};

#endif  // EXPORTDIALOG_HPP
