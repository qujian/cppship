#include <cstdlib>
#include <gsl/narrow>
#include <spdlog/spdlog.h>

#include "cppship/cmd/build.h"
#include "cppship/cmd/install.h"
#include "cppship/core/manifest.h"
#include "cppship/util/log.h"

using namespace cppship;

int cmd::run_install([[maybe_unused]] const BuildOptions& options)
{
    // TODO: fix me
#ifdef _WINNDOWS
    throw Error { "install is not supported in Windows" };
#else
    BuildContext ctx(options.build_type);
    const int result = run_build(ctx, { 
        .build_type = options.build_type
    });
    if (result != 0) {
        return EXIT_FAILURE;
    }

    Manifest manifest(ctx.metafile);
    const auto bin_file = ctx.profile_dir / manifest.name();
    if (!fs::exists(bin_file)) {
        warn("no binary to install");
        return EXIT_SUCCESS;
    }

    const auto dst = fmt::format("/usr/local/bin/{}", manifest.name());
    status("install", "{} to {}", bin_file.string(), dst);
    fs::copy_file(bin_file, dst, fs::copy_options::overwrite_existing);
    return EXIT_SUCCESS;
#endif
}