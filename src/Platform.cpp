#include <memory>

#include "Platforms.hpp"

std::unique_ptr<Platform> Platform::fromJson(const QJsonObject &object) {
    QString platformName = object["platform"].toString();
    if (platformName.isEmpty()) {
        qWarning() << tr("Platform name is empty or not found in JSON object");
        return nullptr;
    }

    auto it = PlatformID.find(platformName);
    if (it != PlatformID.end()) {
        return it->second();
    } else {
        return std::make_unique<Platform>(platformName, QIcon(""));
    }
}
