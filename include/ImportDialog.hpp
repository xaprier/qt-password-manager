#ifndef IMPORTDIALOG_HPP
#define IMPORTDIALOG_HPP

#include <QFileDialog>
#include <QtGlobal>

class ImportDialog : public QFileDialog {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ImportDialog)
  public:
    explicit ImportDialog(QWidget *parent = nullptr);
    ~ImportDialog() override = default;
    [[nodiscard]] QStringList getSelectedFiles() const;

  private slots:
    void onFilesSelected(const QStringList &files);

  private:
    QStringList m_selectedFiles;
};

#endif  // IMPORTDIALOG_HPP
