#pragma once

#include <optional>
#include <string>

#include "cppship/core/profile.h"

namespace cppship::cmd {

struct RunOptions {
    BuildType build_type = BuildType::debug;
    std::string profile;
    std::string args;
    std::optional<std::string> bin;
    std::optional<std::string> example;
};

int run_run(const RunOptions& options);

}