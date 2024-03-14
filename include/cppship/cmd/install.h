#pragma once

#include "cppship/core/profile.h"
#include "cppship/cmd/build.h"
namespace cppship::cmd {

struct InstallOptions {
    BuildType build_type = BuildType::debug;
    std::string profile;
};

int run_install(const BuildOptions& options);

}