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

auto CLIArgumentParser::parse(int argc, char **argv) -> std::expected<CLIArguments, int>
{
    CLI::App app{"Fast Fourier Visualizer"};

    std::string input;
    app.add_option("-i,--input", input, "Input type, available: demo, stdin")->required();

    try
    {
        (app).parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return std::unexpected((app).exit(e));
    }

    auto optInputType = parseInputType(input);

    if (!optInputType)
    {
        std::cerr << "Failed to parse input. Available values: demo, stdin.\n";
        return std::unexpected(1);
    }
    return CLIArguments{.m_inputType = optInputType.value()};
}
