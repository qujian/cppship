#pragma once

#include <optional>
#include <string>

#include "cppship/core/profile.h"
#include "cppship/cmd/build.h"
namespace cppship::cmd {

struct TestOptions {
    std::optional<std::string> target;
    std::optional<std::string> name_regex;
    bool rerun_failed = false;
};

int run_test(BuildOptions& build_opts, const TestOptions& options);

}