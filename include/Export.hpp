#ifndef EXPORT_HPP
#define EXPORT_HPP

#include <QMessageBox>
#include <QObject>
#include <QStandardPaths>

#include "ExportDialog.hpp"
#include "Logger.hpp"

class Export : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(Export)
  public:
    explicit Export(QObject *base = nullptr);
    ~Export() override = default;

  private:
};

#endif  // EXPORT_HPP