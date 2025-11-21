#pragma once

#include "cliarguments.h"
#include <expected>
#include <string>

namespace ffv
{
    class CLIArgumentParser final
    {
    public:
        static auto parse(int argc, char **argv) -> std::expected<CLIArguments, std::string>;
    };
}
