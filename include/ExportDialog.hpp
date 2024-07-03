#ifndef EXPORTDIALOG_HPP
#define EXPORTDIALOG_HPP

#include <qglobal.h>

#include <QFileDialog>

class ExportDialog : public QFileDialog {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ExportDialog)
  public:
    explicit ExportDialog(QWidget *parent = nullptr);
    ~ExportDialog() override;
    [[nodiscard]] QString getSelectedDirectory() const;
    [[nodiscard]] QStringList getSelectedFiles() const;

  private:
    QStringList m_selectedFiles;
};

#endif  // EXPORTDIALOG_HPP
