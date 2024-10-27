#ifndef DIR_HPP
#define DIR_HPP

#include <QDir>

class Dir {
  public:
    virtual ~Dir() = default;

    // Pure virtual functions to be implemented by derived classes
    virtual QString GetPath() const = 0;
    virtual void SetPath(const QString& path) = 0;
};

#endif  // DIR_HPP