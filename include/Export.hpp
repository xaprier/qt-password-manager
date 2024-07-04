#ifndef EXPORT_HPP
#define EXPORT_HPP

#include <QDebug>
#include <QMessageBox>
#include <QObject>
#include <QSettings>

#include "ExportDialog.hpp"

class Export : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(Export)
  public:
    explicit Export(QObject *base = nullptr);
    ~Export() override = default;

  private:
};

#endif  // EXPORT_HPP