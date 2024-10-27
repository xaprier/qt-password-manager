#ifndef IMPORTDIALOG_HPP
#define IMPORTDIALOG_HPP

#include <QComboBox>
#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLayoutItem>
#include <QToolButton>
#include <QtGlobal>

/**
 * todo: handle selection of datadir to import path
 * inspect ExportDialog
 */
// todo: make it singleton
class ImportDialog : public QFileDialog {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ImportDialog)
  public:
    explicit ImportDialog(QWidget *parent = nullptr);
    ~ImportDialog() override = default;
    [[nodiscard]] QStringList GetSelectedFiles() const;
    [[nodiscard]] QString GetSelectedDataDirectory() const;

  private slots:
    void OnFilesSelected(const QStringList &files);
    void OnToolButtonClicked(bool clicked);
    void sl_Accepted();

  private:
    void UpdateDataDirSelectionList();

  private:
    QStringList m_SelectedFiles;
    QLabel *m_Label;
    QComboBox *m_DataDirSelectionBox;
    QToolButton *m_StartDataDirHandlerDialogButton;
};

#endif  // IMPORTDIALOG_HPP
