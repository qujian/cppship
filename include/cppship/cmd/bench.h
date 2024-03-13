#pragma once

#include <optional>
#include <string>

#include "cppship/core/profile.h"

namespace cppship::cmd {

struct BenchOptions {
    BuildType build_type = BuildType::release;
    std::string profile;
    std::optional<std::string> target;
};

int run_bench(const BenchOptions& options);

}