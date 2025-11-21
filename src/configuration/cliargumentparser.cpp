#include "cliargumentparser.h"

#include <CLI/CLI.hpp>
#include <string_view>

#include "../foundation/stringcomparision.h"

using namespace ffv;

namespace
{
    auto parseInputType(std::string_view input) -> std::optional<CLIArguments::InputType>
    {
        if (caseInsensitiveEquals(input, "demo"))
            return CLIArguments::InputType::DEMO;
        if (caseInsensitiveEquals(input, "stdin"))
            return CLIArguments::InputType::STDIN;
        return std::nullopt;
    }
}

auto CLIArgumentParser::parse(int argc, char **argv) -> std::expected<CLIArguments, std::string>
{
    CLI::App app{"Fast Fourier Visualizer"};

    std::string input;
    app.add_option("-i,--input", input, "Input type, available: demo, stdin")->required();

    try
    {
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return std::unexpected(std::format("err code: {}", app.exit(e)));
    }

    auto optInputType = parseInputType(input);

    if (!optInputType)
    {
        return std::unexpected("Failed to parse input. Available values: demo, stdin.\n");
    }
    return CLIArguments{.m_inputType = optInputType.value()};
}
