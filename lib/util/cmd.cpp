#include "cppship/util/cmd.h"
#include "cppship/util/io.h"
#include "cppship/util/log.h"

#include <boost/process/search_path.hpp>
#include <fmt/core.h>

using namespace cppship;
using namespace boost::process;

bool cppship::has_cmd(std::string_view cmd)
{
    const auto path = search_path(cmd);
    return !path.empty();
}

int cppship::run_cmd(const std::string_view cmd)
{
    status("cmd", "run_cmd: {}", cmd);
    return system(std::string { cmd }, shell);
}

int cppship::run_cmd_async(const std::string_view cmd)
{
    ipstream pipe;
    status("cmd", "run_cmd_async: {}", cmd);
    child exe(std::string { cmd }, (std_out & std_err) > pipe, shell);

    std::string line;
    while (exe.running() && std::getline(pipe, line)) {
        spdlog::info(line);
    }

    exe.wait();
    return exe.exit_code();
}

std::string cppship::run_cmd_output(std::string_view cmd)
{
    pstream pipe;
    status("cmd", "run_cmd_output: {}", cmd);
    const int res = system(std::string(cmd), std_out > pipe, shell);
    if (res != 0) {
        throw RunCmdFailed(res, cmd);
    }

    return read_as_string(pipe);
}