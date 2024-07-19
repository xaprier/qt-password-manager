#ifndef ENCFILELISTLOADER_HPP
#define ENCFILELISTLOADER_HPP

#include <QComboBox>
#include <QDir>
#include <QFileInfoList>
#include <QStandardPaths>
#include <QString>

class EncFileListLoader {
  public:
    EncFileListLoader(QComboBox* comboBox);
    void loadEncFiles();

  private:
    QComboBox* comboBox;
};

#endif  // ENCFILELISTLOADER_HPP