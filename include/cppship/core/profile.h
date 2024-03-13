#pragma once

#include <optional>
#include <set>
#include <string>
#include <string_view>
#include <vector>

#include <boost/algorithm/string/case_conv.hpp>

#include "cppship/core/cfg.h"
#include "cppship/exception.h"

namespace cppship {

struct InvalidProfile : public Error {
    InvalidProfile()
        : Error("invalid profile, only Debug/Release is supported")
    {
    }
};

inline constexpr std::string_view kBuildDebug = "Debug";
inline constexpr std::string_view kBuildRelease = "Release";

enum class BuildType { debug, release };

inline std::string_view to_string(BuildType profile)
{
    switch (profile) {
    case BuildType::debug:
        return kBuildDebug;

    case BuildType::release:
        return kBuildRelease;
    }

    std::abort();
}

inline BuildType parse_profile(std::string profile)
{
    boost::to_lower(profile);

    if (profile == "debug") {
        return BuildType::debug;
    }

    if (profile == "release") {
        return BuildType::release;
    }

    throw InvalidProfile {};
}

struct ProfileConfig {
    std::vector<std::string> cxxflags;
    std::vector<std::string> linkflags;
    std::vector<std::string> definitions;
    std::optional<bool> ubsan;
    std::optional<bool> tsan;
    std::optional<bool> asan;
    std::optional<bool> leak;
};

struct ConditionConfig {
    core::CfgPredicate condition;
    ProfileConfig config;
};

struct ProfileOptions {
    ProfileConfig config;
    std::vector<ConditionConfig> conditional_configs;
};

}