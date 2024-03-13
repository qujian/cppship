#pragma once

#include <optional>
#include <string>

#include "cppship/core/profile.h"

namespace cppship::cmd {

struct TestOptions {
    BuildType build_type = BuildType::debug;
    std::string profile;
    std::optional<std::string> target;
    std::optional<std::string> name_regex;
    bool rerun_failed = false;
};

int run_test(const TestOptions& options);

}