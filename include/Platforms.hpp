#ifndef PLATFORMS_HPP
#define PLATFORMS_HPP

#include "Platform.hpp"

// Platform specific data
struct InstagramData {
    static QString name() { return "Instagram"; }
    static QString iconPath() { return ":/platforms/instagram.svg"; }
};

struct GoogleData {
    static QString name() { return "Google"; }
    static QString iconPath() { return ":/platforms/google.svg"; }
};

struct RedditData {
    static QString name() { return "Reddit"; }
    static QString iconPath() { return ":/platforms/reddit.svg"; }
};

struct DiscordData {
    static QString name() { return "Discord"; }
    static QString iconPath() { return ":/platforms/discord.svg"; }
};

struct LinkedInData {
    static QString name() { return "LinkedIn"; }
    static QString iconPath() { return ":/platforms/linkedin.svg"; }
};

struct GitHubData {
    static QString name() { return "GitHub"; }
    static QString iconPath() { return ":/platforms/github.svg"; }
};

struct GitLabData {
    static QString name() { return "GitLab"; }
    static QString iconPath() { return ":/platforms/gitlab.svg"; }
};

struct MicrosoftData {
    static QString name() { return "Microsoft"; }
    static QString iconPath() { return ":/platforms/microsoft.svg"; }
};

struct SteamData {
    static QString name() { return "Steam"; }
    static QString iconPath() { return ":/platforms/steam.svg"; }
};

struct EpicData {
    static QString name() { return "Epic"; }
    static QString iconPath() { return ":/platforms/epic.svg"; }
};

struct OtherData {
    static QString name() { return "Other"; }
    static QString iconPath() { return ":/platforms/other.svg"; }
};

// Derived classes using PlatformTemplate
using Instagram = PlatformTemplate<InstagramData>;
using Google = PlatformTemplate<GoogleData>;
using Reddit = PlatformTemplate<RedditData>;
using Discord = PlatformTemplate<DiscordData>;
using LinkedIn = PlatformTemplate<LinkedInData>;
using GitHub = PlatformTemplate<GitHubData>;
using GitLab = PlatformTemplate<GitLabData>;
using Microsoft = PlatformTemplate<MicrosoftData>;
using Steam = PlatformTemplate<SteamData>;
using Epic = PlatformTemplate<EpicData>;
using Other = PlatformTemplate<OtherData>;

const std::map<QString, std::function<std::unique_ptr<Platform>()>> PlatformID = {
    {"Instagram", []() { return std::make_unique<Instagram>(); }},
    {"Google", []() { return std::make_unique<Google>(); }},
    {"Reddit", []() { return std::make_unique<Reddit>(); }},
    {"Discord", []() { return std::make_unique<Discord>(); }},
    {"LinkedIn", []() { return std::make_unique<LinkedIn>(); }},
    {"GitHub", []() { return std::make_unique<GitHub>(); }},
    {"Microsoft", []() { return std::make_unique<Microsoft>(); }},
    {"Steam", []() { return std::make_unique<Steam>(); }},
    {"Epic", []() { return std::make_unique<Epic>(); }},
    {"Other", []() { return std::make_unique<Other>(); }}};

#endif  // PLATFORMS_HPP