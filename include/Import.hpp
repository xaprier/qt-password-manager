#ifndef IMPORT_HPP
#define IMPORT_HPP

#include <QMessageBox>
#include <QObject>
#include <QSettings>

#include "ImportDialog.hpp"
#include "Logger.hpp"

class Import : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(Import)
  public:
    explicit Import(QObject *base = nullptr);
    ~Import() override = default;

  private:
};

#endif  // IMPORT_HPP