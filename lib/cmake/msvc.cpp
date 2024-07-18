#include "cppship/cmake/msvc.h"
#include "cppship/util/cmd.h"

#include <boost/algorithm/string.hpp>

using namespace cppship;

fs::path msvc::fix_bin(const cppship::cmd::BuildContext& ctx, std::string_view bin)
{
    const auto profile = run_cmd_output(fmt::format("conan profile show {}", ctx.profile));
    if (boost::contains(profile, "compiler=msvc")) {
        return fs::path(to_string(ctx.build_type)) / bin;
    }

    return bin;
}