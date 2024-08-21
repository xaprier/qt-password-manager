#ifndef PLATFORMS_HPP
#define PLATFORMS_HPP

#include <memory>

#include "Platform.hpp"

// Platform specific data
struct DiscordData {
    static QString name() { return "Discord"; }
    static QString iconPath() { return ":/platforms/discord.svg"; }
};

struct EpicData {
    static QString name() { return "Epic"; }
    static QString iconPath() { return ":/platforms/epic.svg"; }
};

struct GitHubData {
    static QString name() { return "GitHub"; }
    static QString iconPath() { return ":/platforms/github.svg"; }
};

struct GitLabData {
    static QString name() { return "GitLab"; }
    static QString iconPath() { return ":/platforms/gitlab.svg"; }
};

struct GoogleData {
    static QString name() { return "Google"; }
    static QString iconPath() { return ":/platforms/google.svg"; }
};

struct InstagramData {
    static QString name() { return "Instagram"; }
    static QString iconPath() { return ":/platforms/instagram.svg"; }
};

struct LinkedInData {
    static QString name() { return "LinkedIn"; }
    static QString iconPath() { return ":/platforms/linkedin.svg"; }
};

struct MicrosoftData {
    static QString name() { return "Microsoft"; }
    static QString iconPath() { return ":/platforms/microsoft.svg"; }
};

struct RedditData {
    static QString name() { return "Reddit"; }
    static QString iconPath() { return ":/platforms/reddit.svg"; }
};

struct SteamData {
    static QString name() { return "Steam"; }
    static QString iconPath() { return ":/platforms/steam.svg"; }
};

struct OtherData {
    static QString name() { return "Other"; }
    static QString iconPath() { return ":/platforms/other.svg"; }
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