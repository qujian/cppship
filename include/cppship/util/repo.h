#pragma once

#include <set>
#include <string_view>

#include "cppship/util/fs.h"

namespace cppship {

inline constexpr std::string_view kRepoConfigFile = "cppship.toml";
inline constexpr std::string_view kIncludePath = "include";
inline constexpr std::string_view kSrcPath = "src";
inline constexpr std::string_view kLibPath = "lib";
inline constexpr std::string_view kTestsPath = "tests";
inline constexpr std::string_view kBenchesPath = "benches";

inline constexpr std::string_view kBuildPath = "build";

inline constexpr std::string_view kRepoHead = "HEAD";

fs::path get_project_root();

std::set<fs::path> list_sources(std::string_view dir);
std::set<fs::path> list_all_files();
std::set<fs::path> list_changed_files(std::string_view commit);

}