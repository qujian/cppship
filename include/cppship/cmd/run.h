#pragma once

#include <optional>
#include <string>

#include "cppship/core/profile.h"
#include "cppship/cmd/build.h"
namespace cppship::cmd {

struct RunOptions {
    std::string args;
    std::optional<std::string> bin;
    std::optional<std::string> example;
};

int run_run(BuildOptions& build_opts, const RunOptions& options);

}