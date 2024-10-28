#ifndef IMPORTDIALOG_HPP
#define IMPORTDIALOG_HPP

#include <QComboBox>
#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLayoutItem>
#include <QToolButton>
#include <QtGlobal>

#include "singleton.hpp"

class ImportDialog : public QFileDialog {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ImportDialog)
  public:
    friend Singleton<ImportDialog>;
    [[nodiscard]] QStringList GetSelectedFiles() const;
    [[nodiscard]] QString GetSelectedDataDirectory() const;

  private slots:
    void sl_OnFilesSelected(const QStringList &files);
    void sl_OnToolButtonClicked(bool clicked);
    void sl_Accepted();

  private:
    explicit ImportDialog(QWidget *parent = nullptr);
    ~ImportDialog() override = default;
    void _UpdateDataDirSelectionList();

  private:
    QStringList m_selectedFiles;
    QLabel *m_label;
    QComboBox *m_dataDirSelectionBox;
    QToolButton *m_execDataDirHandlerDialogButton;
};

#endif  // IMPORTDIALOG_HPP
