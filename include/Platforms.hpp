#ifndef PLATFORMS_HPP
#define PLATFORMS_HPP

#include <memory>

#include "Platform.hpp"

// Platform specific data
struct DiscordData {
    static QString Name() { return "Discord"; }
    static QString IconPath() { return ":/platforms/discord.svg"; }
};

struct EpicData {
    static QString Name() { return "Epic"; }
    static QString IconPath() { return ":/platforms/epic.svg"; }
};

struct GitHubData {
    static QString Name() { return "GitHub"; }
    static QString IconPath() { return ":/platforms/github.svg"; }
};

struct GitLabData {
    static QString Name() { return "GitLab"; }
    static QString IconPath() { return ":/platforms/gitlab.svg"; }
};

struct GoogleData {
    static QString Name() { return "Google"; }
    static QString IconPath() { return ":/platforms/google.svg"; }
};

struct InstagramData {
    static QString Name() { return "Instagram"; }
    static QString IconPath() { return ":/platforms/instagram.svg"; }
};

struct LinkedInData {
    static QString Name() { return "LinkedIn"; }
    static QString IconPath() { return ":/platforms/linkedin.svg"; }
};

struct MicrosoftData {
    static QString Name() { return "Microsoft"; }
    static QString IconPath() { return ":/platforms/microsoft.svg"; }
};

struct RedditData {
    static QString Name() { return "Reddit"; }
    static QString IconPath() { return ":/platforms/reddit.svg"; }
};

struct SteamData {
    static QString Name() { return "Steam"; }
    static QString IconPath() { return ":/platforms/steam.svg"; }
};

struct OtherData {
    static QString Name() { return "Other"; }
    static QString IconPath() { return ":/platforms/other.svg"; }
};

// Derived classes using PlatformTemplate
using Discord = PlatformTemplate<DiscordData>;
using Epic = PlatformTemplate<EpicData>;
using GitHub = PlatformTemplate<GitHubData>;
using GitLab = PlatformTemplate<GitLabData>;
using Google = PlatformTemplate<GoogleData>;
using Instagram = PlatformTemplate<InstagramData>;
using LinkedIn = PlatformTemplate<LinkedInData>;
using Microsoft = PlatformTemplate<MicrosoftData>;
using Reddit = PlatformTemplate<RedditData>;
using Steam = PlatformTemplate<SteamData>;
using Other = PlatformTemplate<OtherData>;

const std::map<QString, std::function<std::unique_ptr<Platform>()>> PlatformID = {
    {"Discord", []() { return std::make_unique<Discord>(); }},
    {"Epic", []() { return std::make_unique<Epic>(); }},
    {"GitHub", []() { return std::make_unique<GitHub>(); }},
    {"GitLab", []() { return std::make_unique<GitLab>(); }},
    {"Google", []() { return std::make_unique<Google>(); }},
    {"Instagram", []() { return std::make_unique<Instagram>(); }},
    {"LinkedIn", []() { return std::make_unique<LinkedIn>(); }},
    {"Microsoft", []() { return std::make_unique<Microsoft>(); }},
    {"Reddit", []() { return std::make_unique<Reddit>(); }},
    {"Steam", []() { return std::make_unique<Steam>(); }},
    {"Other", []() { return std::make_unique<Other>(); }}};

#endif  // PLATFORMS_HPP