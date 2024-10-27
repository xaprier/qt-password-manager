#include "DataDirs.hpp"

#include "ConfigManager.hpp"
#include "singleton.hpp"

DataDirs::DataDirs() : m_Manager(Singleton<ConfigManager>::Instance()) {
    m_Manager.LoadDataDirs(*this);
}

void DataDirs::SaveDataDirs() {
    m_Manager.SaveDataDirs(*this);
}

void DataDirs::AddDataDir(const DataDir& dataDir) {
    for (const auto& dir : this->m_DataDirs)
        if (dir.GetPath() == dataDir.GetPath()) return;  // filter same path

    m_DataDirs.append(dataDir);
    this->SaveDataDirs();
}

void DataDirs::RemoveDataDir(int index) {
    if (index >= 0 && index < m_DataDirs.size()) {
        m_DataDirs.removeAt(index);
    }
    this->SaveDataDirs();
}

void DataDirs::UpdateDataDir(int index, const QString& path) {
    if (index >= 0 && index < m_DataDirs.size()) {
        this->m_DataDirs[index].SetPath(path);
    }
    this->SaveDataDirs();
}

const QVector<DataDir> DataDirs::GetDataDirs() const {
    return m_DataDirs;
}

void DataDirs::ClearDataDirs() {
    this->m_DataDirs.clear();
    //! if we save data after clear function, the data can be lost when closing program immediately
    // this->SaveDataDirs();
}