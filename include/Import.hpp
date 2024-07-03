#ifndef IMPORT_HPP
#define IMPORT_HPP

#include <qglobal.h>
#include <qobject.h>
#include <qobjectdefs.h>

/**
 * @brief This class should create an file dialog with multiple file selection.
 *        file selection filter must be .enc extension files, and selected files copied to the correct directory
 *
 */
class Import : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(Import)
  public:
    explicit Import(QObject *base = nullptr);
    ~Import() override;

  private:
};

#endif  // IMPORT_HPP