#pragma once

#include <set>
#include <string>
#include <thread>

#include <boost/algorithm/string/case_conv.hpp>
#include <gsl/narrow>

#include "cppship/core/dependency.h"
#include "cppship/core/layout.h"
#include "cppship/core/manifest.h"
#include "cppship/core/profile.h"
#include "cppship/util/fs.h"
#include "cppship/util/repo.h"

namespace cppship::cmd {

enum BuildGroup { lib, binaries, examples, tests, benches };

struct BuildOptions {
    int max_concurrency = gsl::narrow_cast<int>(std::thread::hardware_concurrency());
    BuildType build_type = BuildType::debug;
    std::string profile;
    bool dry_run = false;
    std::optional<std::string> target;
    std::set<BuildGroup> groups;
    std::optional<std::string> custom_profile;
};

struct BuildContext {
    BuildType build_type = BuildType::debug;
    fs::path root = get_project_root();
    fs::path build_dir = root / kBuildPath;
    fs::path deps_dir = build_dir / "deps";
    fs::path profile_dir = build_dir / boost::to_lower_copy(std::string(to_string(build_type)));
    fs::path metafile = root / "cppship.toml";
    fs::path conan_file = build_dir / "conanfile.txt";
    fs::path git_dep_file = build_dir / "git_dep.toml";
    fs::path conan_profile_path = profile_dir / "conan_profile";
    fs::path inventory_file = profile_dir / "inventory.toml";
    fs::path dependency_file = profile_dir / "dependency.toml";

    Manifest manifest { metafile };
    Layout layout { root, manifest.name() };

    explicit BuildContext(BuildType build_type_)
        : build_type(build_type_)
    {
        if (!fs::exists(build_dir)) {
            fs::create_directories(build_dir);
        }
    }

    [[nodiscard]] bool is_expired(const fs::path& path) const
    {
        return !fs::exists(path) || fs::last_write_time(path) < fs::last_write_time(metafile);
    }
};

std::string get_default_profile_path();

int run_build(BuildContext& ctx, const BuildOptions& options);

int get_conan_version(const BuildContext& ctx);

void conan_detect_profile(const BuildContext& ctx);

void conan_setup(const BuildContext& ctx);

void conan_install(const BuildContext& ctx);

void cppship_install(
    const BuildContext& ctx, const ResolvedDependencies& cppship_deps, const ResolvedDependencies& all_deps);

void cmake_setup(const BuildContext& ctx);

int cmake_build(const BuildContext& ctx, const BuildOptions& options);

}