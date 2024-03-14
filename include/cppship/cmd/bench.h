#pragma once

#include <optional>
#include <string>

#include "cppship/core/profile.h"
#include "cppship/cmd/build.h"
namespace cppship::cmd {

struct BenchOptions {
    std::optional<std::string> target;
};

int run_bench(BuildOptions& build_options, const BenchOptions& options);

}