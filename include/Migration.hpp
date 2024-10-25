#ifndef MIGRATIONOLDDATATONEW_HPP
#define MIGRATIONOLDDATATONEW_HPP

#include "MigrationException.hpp"

class Migration {
  public:
    virtual void migrate() = 0;
};

#endif  // MIGRATIONOLDDATATONEW_HPP