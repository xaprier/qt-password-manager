#ifndef DATADIRS_HPP
#define DATADIRS_HPP

#include <qglobal.h>

#include <QObject>
#include <QVector>

#include "DataDir.hpp"
#include "singleton.hpp"
class ConfigManager;
class DataDirs : public QObject {
    Q_DISABLE_COPY_MOVE(DataDirs)
  public:
    friend class Singleton<DataDirs>;

    void AddDataDir(const DataDir& dataDir);

    void RemoveDataDir(int index);

    void UpdateDataDir(int index, const QString& path);

    const QVector<DataDir> GetDataDirs() const;

    void ClearDataDirs();

  private:
    void SaveDataDirs();
    DataDirs();
    ~DataDirs() = default;
    ConfigManager& m_Manager;
    QVector<DataDir> m_DataDirs;
};

#endif  // DATADIRS_HPP