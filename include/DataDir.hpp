#ifndef DATADIR_HPP
#define DATADIR_HPP

#include "Dir.hpp"

class DataDir : public Dir {
  public:
    explicit DataDir(const QString& path = "") : dir(path) {}

    QString GetPath() const override {
        return dir.absolutePath();
    }

    void SetPath(const QString& path) override {
        dir.setPath(path);
    }

  private:
    QDir dir;
};

#endif  // DATADIR_HPP